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

namespace stemaj {
struct FontsImpl
{
  struct FontContainer
  {
    std::string name;
    FontSize size;
    std::unique_ptr<olc::Font> font;
  };
  std::vector<FontContainer> _fonts;
};
}

Fonts::Fonts() : _impl(new FontsImpl())
{
	
}

Fonts::~Fonts()
{
	delete _impl;
}

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
		for (int i = 0; i < (int)FontSize::COUNT; i++)
		{
      _impl->_fonts.push_back({
        sName,
        (FontSize)i,
        std::make_unique<olc::Font>(sFileName, toInt((FontSize)i))
        });
		}
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

olc::Font* Fonts::Font(const std::string& name, const FontSize fontSize)
{
  for (auto& a : _impl->_fonts)
  {
    if (a.name == name && a.size == fontSize)
    {
      return a.font.get();
    }
  }
  throw;
  return nullptr;
}

int Fonts::toInt(FontSize f)
{
  float fac = std::min(CO.W,CO.H);
  auto ret = 0;

  switch (f)
  {
		case FontSize::SMALL:
			ret = int((float)fac * 0.05f);
      break;
		case FontSize::NORMAL:
			ret = int((float)fac * 0.1f);
      break;
		case FontSize::BIG:
      ret = int((float)fac * 0.5f);
      break;
    default:
      throw;
  }
  return ret;
}

PT<int> Fonts::BoxSize(const std::string& text, olc::Font* fontPtr)
{
  auto r = fontPtr->RenderStringToDecal(
    utf8::utf8to32(std::string(text)), olc::WHITE);

  return { r->sprite->width, r->sprite->height};
}
