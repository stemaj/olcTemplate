#include "olcTemplate/game/src/engine/olcUTIL_Animate2D.h"
#include <array>
#include <olcTemplate/game/animation.hpp>
#include <olcTemplate/game/assets.hpp>
#include <olcTemplate/game/loadsave.hpp>
#include <unordered_map>
#include <vector>
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

  for (const auto& entry : fs::directory_iterator(directory))
  {
    if (!entry.is_regular_file() || entry.path().extension() != ".lua")
    {
      continue;      
    }

    LS.Init(entry.path(), false);

    stemaj::Animation a;
    a.spriteWidth = LS.Int("spriteWidth");
    a.spriteHeight = LS.Int("spriteHeight");
    a.ox = LS.Float("ox");
    a.oy = LS.Float("oy");

    auto frameDurations = LS.Map<int, float>("frame_duration");
    auto frameStyles = LS.Map<int,int>("frame_style");
    auto details = LS.Map<int, std::vector<std::array<int,2>>>("details");

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

Task AnimationMap::Load()
{
  LoadFrom("./assets/sheets");
  LoadFrom("./olcTemplate/assets/sheets");

  Loaded = true;
  std::cout << "Animations loaded\n";

  co_return;
}
