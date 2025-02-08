#include <olcTemplate/game/assets.hpp>
#include <olcTemplate/game/src/engine/olcPixelGameEngine.h>

#include <filesystem>
#include <utility>
#include <memory>

using namespace stemaj;
namespace fs = std::filesystem;

Assets& stemaj::Assets::get()
{
  static Assets me;
  return me;
}

Task Assets::Load()
{
  auto loadSprite = [&](const std::string& sName, 
    const std::string& sFileName)
  {
    auto s = std::make_unique<olc::Renderable>();
    s->Load(sFileName);
    _renderables[sName] = std::move(s);
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
    if (spritesheet->Load(sFileName) != olc::rcode::OK)
    {
      std::cout << "could not load spritesheet " << sFileName << std::endl;
    }
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

  co_return;
}

olc::Sprite* Assets::Sprite(const std::string& name)
{
  return _renderables[name]->Sprite();
}

olc::Decal* Assets::Decal(const std::string& name)
{
  return _renderables[name]->Decal();
}

olc::Renderable* Assets::Renderable(const std::string& name)
{
  return _renderables[name].get();
}
