#ifndef __FONTS_HPP
#define __FONTS_HPP

#include <memory>
#include <olcTemplate/game/coordinates.hpp>
#include <olcTemplate/game/guiElements.hpp>
#include <string>
#include <olcTemplate/game/src/state/loading.hpp>


namespace olc {
	class Font;
	class Decal;
	class Renderable;
}

namespace stemaj {

class FontsImpl;

class Fonts
{
public:
	
	static Fonts& get();
	Fonts(Fonts const&) = delete;
	void operator=(Fonts const&) = delete;
	
	olc::Font* Font(const std::string& name, const FontSize fontSize);
	
	Task Load();
	bool Loaded = false;
	
	PT<int> BoxSize(const std::string& text, const std::string& fontName, const FontSize fontSize);
	std::shared_ptr<olc::Renderable> Renderable(const std::string& text,
		const std::string& fontName, const FontSize fontSize, const uint32_t color = 0xFFFFFFFF);

private:
	Fonts();
	virtual ~Fonts();
	
	int toInt(FontSize f);

	std::unique_ptr<FontsImpl> _impl;
};

#define FT Fonts::get()

} // namespace stemaj

#endif //__ASSETS_HPP
