#include <game/assets.hpp>
#include <filesystem>
#include <utility>

#include <memory>

#define OLC_IGNORE_VEC2D
#include <game/src/engine/utilities/olcUTIL_Geometry2D.h>
#include <game/src/engine/olcUTIL_Animate2D.h>
#include <game/src/engine/olcPixelGameEngine.h>

#define SOL_ALL_SAFETIES_ON 1
#include <sdk/sol2-3.3.0/sol.hpp>

using namespace stemaj;
namespace fs = std::filesystem;
using olc::utils::Animate2D::Animation;
using olc::utils::Animate2D::FrameSequence;

Assets& stemaj::Assets::get()
{
  static Assets me;
  return me;
}

void Assets::Load()
{
  auto loadSprite = [&](const std::string& sName, 
    const std::string& sFileName)
  {
    auto s = std::make_unique<olc::Sprite>(sFileName);
    auto d = std::make_unique<olc::Decal>(s.get());
		_sprites[sName] = std::move(s);
    _decals[sName] = std::move(d);
	};

  std::string directory = "./assets/png";
  for (const auto& entry : fs::directory_iterator(directory))
  {
    if (entry.is_regular_file() && entry.path().extension() == ".png")
    {
      loadSprite(entry.path().stem().string(), entry.path().string());
    }
  }

  auto loadSpriteSheet = [&](const std::string& sName, 
    const std::string& sFileName)
  {
    auto spritesheet = std::make_unique<olc::Renderable>();
    spritesheet->Load(sFileName);

    sol::state lua;
    lua.open_libraries(sol::lib::base, sol::lib::io, sol::lib::math, sol::lib::table);
    try
    {
      lua.safe_script_file("./assets/sheets/" + sName + ".lua");
    }
    catch (const sol::error& e)
    {
      std::cout << std::string(e.what()) << std::endl;
    }

    auto container = std::make_unique<AnimationContainer>();
    container->spriteWidth = lua["spriteWidth"];
    container->spriteHeight = lua["spriteHeight"];
    container->ox = lua["ox"];
    container->oy = lua["oy"];
    for (int i = 0; i < AnimationKind::COUNT; i++)
    {
      FrameSequence frameSequence(0.3f);
      auto indicies = lua["details"][i].get<std::vector<std::array<int, 2>>>();
      auto e = static_cast<AnimationKind>(i);
      for (auto& j : indicies)
      {
        auto pair = std::make_pair(j[0],j[1]);
        frameSequence.AddFrame( { spritesheet.get(),
          { {pair.first,pair.second}, 
          {container->spriteWidth, container->spriteHeight} } } );
      }
      container->animation[e] = std::make_unique<olc::utils::Animate2D::Animation<AnimationKind>>();
      container->animation[e]->AddState(e, frameSequence);
    }

    _renderables[sName] = std::move(spritesheet);
    _animationContainers[sName] = std::move(container);
  };

  directory = "./assets/sheets";
  for (const auto& entry : fs::directory_iterator(directory))
  {
    if (entry.is_regular_file() && entry.path().extension() == ".png")
    {
      loadSpriteSheet(entry.path().stem().string(), entry.path().string());
    }
  }
}

olc::Sprite* Assets::Sprite(const std::string& name)
{
  return _sprites[name].get();
}

olc::Decal* Assets::Decal(const std::string& name)
{
  return _decals[name].get();
}

olc::Renderable* Assets::Renderable(const std::string& name)
{
  return _renderables[name].get();
}

AnimationContainer* Assets::Animation(const std::string& name)
{
  return _animationContainers[name].get();
}
