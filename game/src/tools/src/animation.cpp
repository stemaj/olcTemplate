#include <game/src/tools/animation.hpp>
#include <game/assets.hpp>

#define SOL_ALL_SAFETIES_ON 1
#include <sdk/sol2-3.3.0/sol.hpp>

#include <filesystem>

using namespace stemaj;
namespace fs = std::filesystem;

AnimationMap& AnimationMap::get()
{
  static AnimationMap me;
  return me;
}

stemaj::Animation AnimationMap::GetAnimation(const std::string& name)
{
  if (!_loaded) Load();
  return _map[name];
}

void AnimationMap::Load()
{
  std::string sName;
  sol::state lua;
  lua.open_libraries(sol::lib::base, sol::lib::io, sol::lib::math, sol::lib::table);

  std::string directory = "./assets/sheets";
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
    a.spriteWidth = lua["spriteWidth"];
    a.spriteHeight = lua["spriteHeight"];
    a.ox = lua["ox"];
    a.oy = lua["oy"];
    for (int i = 0; i < AnimationKind::COUNT; i++)
    {
      olc::utils::Animate2D::FrameSequence frameSequence(0.3f);
      auto indicies = lua["details"][i].get<std::vector<std::array<int, 2>>>();
      auto e = static_cast<AnimationKind>(i);
      for (auto& j : indicies)
      {
        auto pair = std::make_pair(j[0],j[1]);
        frameSequence.AddFrame( { AS.Renderable(sName),
          { {pair.first,pair.second}, 
          {a.spriteWidth, a.spriteHeight} } } );
      }
      a.animation.AddState(e, frameSequence);
    }
    _map[entry.path().stem()] = a;
  }

  _loaded = true;
}
