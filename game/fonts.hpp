#ifndef __FONTS_HPP
#define __FONTS_HPP

#include <game/coordinates.hpp>
#include <unordered_map>
#include <memory>
#include <string>

namespace olc {
	class Font;
	class Pixel;
	class Decal;
}

namespace stemaj {

enum class FontSize
{
	NORMAL = 0,
	SMALL = 1,
	BIG = 2,
	COUNT = 3
};

class FontsImpl;

class Fonts
{
public:
	
	static Fonts& get();
	Fonts(Fonts const&) = delete;
	void operator=(Fonts const&) = delete;
	
	olc::Font* Font(const std::string& name, const FontSize fontSize);
	
	void Load();
	
	PT<int> BoxSize(const std::string& text, const std::string& fontName, const FontSize fontSize);
	olc::Decal* Decal(const std::string& text, const std::string& fontName, const FontSize fontSize);

private:
	Fonts();
	virtual ~Fonts();
	
	int toInt(FontSize f);
	
	FontsImpl* _impl = nullptr;
};

#define FT Fonts::get()

} // namespace stemaj

#endif //__ASSETS_HPP
