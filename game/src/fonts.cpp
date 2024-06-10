#include <olcTemplate/game/fonts.hpp>
#include <olcTemplate/game/coordinates.hpp>
#include <filesystem>

#include <olcTemplate/game/src/engine/olcPGEX_TTF.h>
#define UTF_CPP_CPLUSPLUS 202002L
#include <olcTemplate/sdk/utfcpp/utf8.h>

using namespace stemaj;
namespace fs = std::filesystem;

namespace stemaj {
class FontsImpl
{
public:
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
  if (fs::exists(directory) && fs::is_directory(directory))
  {
    for (const auto& entry : fs::directory_iterator(directory))
    {
      if (entry.is_regular_file() && entry.path().extension() == ".ttf")
      {
        loadFont(entry.path().stem().string(), entry.path().string());
      }
    }
  }

  directory = "./olcTemplate/assets/fonts";
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
		case FontSize::SMALLEST:
			ret = int((float)fac * 0.02f);
      break;
		case FontSize::SMALLER:
			ret = int((float)fac * 0.05f);
      break;
		case FontSize::SMALL:
			ret = int((float)fac * 0.08f);
      break;
		case FontSize::NORMAL:
			ret = int((float)fac * 0.1f);
      break;
		case FontSize::BIG:
      ret = int((float)fac * 0.15f);
      break;
		case FontSize::BIGGER:
      ret = int((float)fac * 0.25f);
      break;
		case FontSize::BIGGEST:
      ret = int((float)fac * 0.4f);
      break;
    default:
      throw;
  }
  return ret;
}

PT<int> Fonts::BoxSize(const std::string& text, const std::string& fontName, const FontSize fontSize)
{
	for (auto& a : _impl->_fonts)
	{
		if (a.name == fontName && a.size == fontSize)
		{
			auto r = a.font->RenderStringToDecal(
																				 utf8::utf8to32(std::string(text)), olc::WHITE);
			return { r->sprite->width, r->sprite->height};
		}
	}
	return {0,0};
}

olc::Decal* Fonts::Decal(const std::string& text, const std::string& fontName, const FontSize fontSize)
{
	for (auto& a : _impl->_fonts)
	{
		if (a.name == fontName && a.size == fontSize)
		{
			return a.font->RenderStringToDecal(
																				 utf8::utf8to32(std::string(text)), olc::WHITE);
		}
	}
	return nullptr;
}
