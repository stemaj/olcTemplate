#include <olcTemplate/game/animation.hpp>
#include <olcTemplate/game/assets.hpp>

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

stemaj::Animation AnimationMap::GetAnimation(const std::string& name)
{
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
        // std::cout << j[0] << std::endl;
        // std::cout << j[1] << std::endl;
        // std::cout << entry.path().stem() << std::endl;
        // std::cout << a.spriteHeight << std::endl;
        // std::cout << a.spriteWidth << std::endl;
        // std::cout << e << std::endl;

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
