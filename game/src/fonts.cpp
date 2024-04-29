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
class FontsImpl
{
public:
	struct Single
	{
	public:
		Single(std::string name, FontSize size, olc::Font* font) :
		_name(name), _size(size), _font(font) {}
		virtual ~Single() = default;
		std::string _name;
		FontSize _size;
		olc::Font* _font = nullptr;
	};
	std::vector<Single> _fonts;
};
}

Fonts::Fonts() : _impl(new FontsImpl())
{
	
}

Fonts::~Fonts()
{
	for (auto& a : _impl->_fonts)
	{
		delete a._font;
	}
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
			FontsImpl::Single s = {sFileName, (FontSize)i, new olc::Font(sFileName,toInt((FontSize)i))};
			_impl->_fonts.push_back(s);
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
	
	auto it = std::find_if(_impl->_fonts.begin(), _impl->_fonts.end(),
												 [&](const FontsImpl::Single& p) { 
		return name == p._name && fontSize == p._size; });
	return it->_font;
}

int Fonts::toInt(FontSize f)
{
  float fac = std::min(CO.W,CO.H);

  switch (f)
  {
		case FontSize::SMALL:
			return int((float)fac * 0.05f);
		case FontSize::NORMAL:
			return int((float)fac * 0.1f);
		case FontSize::BIG:
			return int((float)fac * 0.5f);
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
