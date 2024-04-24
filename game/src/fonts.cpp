#include <game/fonts.hpp>
#include <filesystem>
#include <unordered_map>
#include <utility>

#include <game/src/engine/olcPGEX_TTF.h>

using namespace stemaj;
namespace fs = std::filesystem;

Fonts& stemaj::Fonts::get()
{
  static Fonts me;
  return me;
}

void Fonts::Load()
{
  olc::Font::init();
  
  auto loadFont = [&](const std::string& sName, 
    const std::string& sFileName)
  {
    // TODO fontsize from settings

    auto font = std::make_shared<olc::Font>(sFileName,40);
    std::unordered_map<int, std::shared_ptr<olc::Font>> map;
    map[40] = std::move(font);
    _fonts[sName] = map;
	};

  std::string directory = "./assets/fonts";
  for (const auto& entry : fs::directory_iterator(directory))
  {
    if (entry.is_regular_file() && entry.path().extension() == ".ttf")
    {
      loadFont(entry.path().stem().string(), entry.path().string());
    }
  }
}

olc::Font* Fonts::Font(const std::string& name, const int fontSize)
{
  auto family = _fonts[name];
  return family[fontSize].get();
}
