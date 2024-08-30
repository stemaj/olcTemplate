#include "olcTemplate/game/src/engine/olcUTIL_Animate2D.h"
#include <olcTemplate/game/animation.hpp>
#include <olcTemplate/game/assets.hpp>
#include <vector>

#define SOL_ALL_SAFETIES_ON 1
#include <olcTemplate/sdk/sol2-3.3.0/sol.hpp>

#include <filesystem>

using namespace stemaj;
namespace fs = std::filesystem;

AnimationMap& AnimationMap::get()
{
  static AnimationMap me;
  return me;
}

stemaj::Animation& AnimationMap::GetAnimation(const std::string& name)
{
  return _map[name];
}

void AnimationMap::LoadFrom(const std::string& directory)
{
  if (!fs::exists(directory) || !fs::is_directory(directory)) return;

  std::string sName;
  sol::state lua;
  lua.open_libraries(sol::lib::base, sol::lib::io, sol::lib::math, sol::lib::table);

  for (const auto& entry : fs::directory_iterator(directory))
  {
    if (!entry.is_regular_file() || entry.path().extension() != ".lua")
    {
      continue;      
    }

    try
    {
      lua.safe_script_file(entry.path().string());
    }
    catch (const sol::error& e)
    {
      std::cout << std::string(e.what()) << std::endl;
    }

    stemaj::Animation a;
    a.spriteWidth = lua["spriteWidth"].get_or(0);
    a.spriteHeight = lua["spriteHeight"].get_or(0);
    a.ox = lua["ox"].get_or(0.0f);
    a.oy = lua["oy"].get_or(0.0f);

    auto frameDurations = lua["frame_duration"].get_or(std::map<int, float>{});
    auto frameStyles = lua["frame_style"].get_or(std::map<int, int>{});

    auto details = lua["details"].get_or<std::map<int, std::vector<std::array<int, 2>>>>({});
    for (int i = 0; i < AnimationKind::COUNT; i++)
    {
      if (!details.contains(i)) continue;

      auto fd = frameDurations.contains(i) ? frameDurations[i] : 0.3f;
      auto fs = frameStyles.contains(i)
        ? (olc::utils::Animate2D::Style)frameStyles[i]
        : olc::utils::Animate2D::Style::Repeat;
      olc::utils::Animate2D::FrameSequence frameSequence(fd, fs);
      auto indicies = details[i];
      auto e = static_cast<AnimationKind>(i);
      for (auto& j : indicies)
      {
        auto pair = std::make_pair(j[0],j[1]);
        frameSequence.AddFrame( { AS.Renderable(entry.path().stem().string()),
          { {pair.first * a.spriteWidth,pair.second * a.spriteHeight}, 
          {a.spriteWidth, a.spriteHeight} } } );
      }
      a.animation.AddState(e, frameSequence);
    }
    _map[entry.path().stem().string()] = a;
  }
}

void AnimationMap::Load()
{
  LoadFrom("./assets/sheets");
  LoadFrom("./olcTemplate/assets/sheets");

  Loaded = true;
  std::cout << "Animations loaded\n";
}
