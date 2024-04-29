#ifndef __FONTS_HPP
#define __FONTS_HPP

#include <game/coordinates.hpp>
#include <unordered_map>
#include <memory>
#include <string>

namespace olc {
	class Font;
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
	
	static PT<int> BoxSize(const std::string& text, olc::Font* fontPtr);
	
private:
	Fonts();
	virtual ~Fonts();
	
	int toInt(FontSize f);
	
	FontsImpl* _impl = nullptr;
};

#define FT Fonts::get()

} // namespace stemaj

#endif //__ASSETS_HPP
