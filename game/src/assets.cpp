#include <olcTemplate/game/assets.hpp>
#include <olcTemplate/game/src/engine/olcPixelGameEngine.h>

#include <filesystem>
#include <utility>
#include <memory>

#define SOL_ALL_SAFETIES_ON 1
#include <olcTemplate/sdk/sol2-3.3.0/sol.hpp>

using namespace stemaj;
namespace fs = std::filesystem;

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
  if (fs::exists(directory) && fs::is_directory(directory))
  {
    for (const auto& entry : fs::directory_iterator(directory))
    {
      if (entry.is_regular_file() && entry.path().extension() == ".png")
      {
        loadSprite(entry.path().stem().string(), entry.path().string());
      }
    }
  }

  directory = "./olcTemplate/assets/png";
  if (fs::exists(directory) && fs::is_directory(directory))
  {
    for (const auto& entry : fs::directory_iterator(directory))
    {
      if (entry.is_regular_file() && entry.path().extension() == ".png")
      {
        loadSprite(entry.path().stem().string(), entry.path().string());
      }
    }
  }

  auto loadSpriteSheet = [&](const std::string& sName, 
    const std::string& sFileName)
  {
    auto spritesheet = std::make_unique<olc::Renderable>();
    spritesheet->Load(sFileName);
    _renderables[sName] = std::move(spritesheet);
  };

  directory = "./assets/sheets";
  if (fs::exists(directory) && fs::is_directory(directory))
  {
    for (const auto& entry : fs::directory_iterator(directory))
    {
      if (entry.is_regular_file() && entry.path().extension() == ".png")
      {
        loadSpriteSheet(entry.path().stem().string(), entry.path().string());
      }
    }
  }

  directory = "./olcTemplate/assets/sheets";
  if (fs::exists(directory) && fs::is_directory(directory))
  {
    for (const auto& entry : fs::directory_iterator(directory))
    {
      if (entry.is_regular_file() && entry.path().extension() == ".png")
      {
        loadSpriteSheet(entry.path().stem().string(), entry.path().string());
      }
    }
  }

  Loaded = true;
  std::cout << "Assets loaded\n";
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
