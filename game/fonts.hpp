#ifndef __FONTS_HPP
#define __FONTS_HPP

#include <memory>
#include <olcTemplate/game/coordinates.hpp>
#include <string>

namespace olc {
	class Font;
	class Decal;
}

namespace stemaj {

enum class FontSize
{
	NORMAL = 0,
	SMALL = 1,
	BIG = 2,
	SMALLER = 3,
	SMALLEST = 4,
	BIGGER = 5,
	BIGGEST = 6,
	COUNT = 7
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
	bool Loaded = false;
	
	PT<int> BoxSize(const std::string& text, const std::string& fontName, const FontSize fontSize);
	olc::Decal* Decal(const std::string& text, const std::string& fontName, const FontSize fontSize);

private:
	Fonts();
	virtual ~Fonts();
	
	int toInt(FontSize f);

	std::unique_ptr<FontsImpl> _impl;
};

#define FT Fonts::get()

} // namespace stemaj

#endif //__ASSETS_HPP
