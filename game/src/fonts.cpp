#include <game/fonts.hpp>
#include <game/coordinates.hpp>
#include <filesystem>
#include <unordered_map>
#include <utility>

#include <game/src/engine/olcPGEX_TTF.h>
#define UTF_CPP_CPLUSPLUS 202002L
#include <sdk/utfcpp/utf8.h>

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
    Fontsize size = Fontsize::NORMAL;

    auto font = std::make_shared<olc::Font>(sFileName,toInt(size));
    std::unordered_map<int, std::shared_ptr<olc::Font>> map;
    map[(int)size] = std::move(font);
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

olc::Font* Fonts::Font(const std::string& name, const Fontsize fontSize)
{
  auto family = _fonts[name];
  return family[(int)fontSize].get();
}

int Fonts::toInt(Fontsize f)
{
  float fac = std::min(CO.W,CO.H);

  switch (f)
  {
  case Fontsize::NORMAL:
    return int(fac * 0.15);
  default:
    throw;
  }
}

PT<int> Fonts::BoxSize(const std::string& text, olc::Font* fontPtr)
{
  auto r = fontPtr->RenderStringToDecal(
    utf8::utf8to32(std::string(text)), olc::WHITE);

  return { r->sprite->width, r->sprite->height};
}

static PT<int> FrameSize(const std::string& text, olc::Font* fontPtr)
{
  auto r = fontPtr->RenderStringToDecal(
    utf8::utf8to32(std::string(text)), olc::WHITE);

  return { r->sprite->width+20, r->sprite->height+20};
}
