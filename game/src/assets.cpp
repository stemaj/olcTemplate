#include <game/assets.hpp>
#include <filesystem>

namespace fs = std::filesystem;

stemaj::Assets& stemaj::Assets::get()
{
  static Assets me;
  return me;
}

void stemaj::Assets::Load()
{
  auto loadSprite = [&](const std::string& sName, 
    const std::string& sFileName)
  {
    auto s = std::make_unique<olc::Sprite>(sFileName);
    auto d = std::make_unique<olc::Decal>(s.get());
		_sprites[sName] = std::make_pair(std::move(s),std::move(d));
	};

  std::string directory = "./assets/png";
  for (const auto& entry : fs::directory_iterator(directory))
  {
    if (entry.is_regular_file() && entry.path().extension() == ".png")
    {
      loadSprite(entry.path().stem(), entry.path());
    }
  }
}

olc::Sprite* stemaj::Assets::Sprite(const std::string& name)
{
  return _sprites[name].first.get();
}

olc::Decal* stemaj::Assets::Decal(const std::string& name)
{
  return _sprites[name].second.get();
}
