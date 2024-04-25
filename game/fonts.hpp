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

enum class Fontsize
{
	NORMAL = 0,
	COUNT = 1
};

class Fonts
{
public:

	static Fonts& get();
	Fonts(Fonts const&) = delete;
	void operator=(Fonts const&) = delete;

  olc::Font* Font(const std::string& name, const Fontsize fontSize);

  void Load();

	static PT<int> BoxSize(const std::string& text, olc::Font* fontPtr);
	static PT<int> FrameSize(const std::string& text, olc::Font* fontPtr);

private:
	Fonts() {}
	virtual ~Fonts() {}	

	int toInt(Fontsize f);

  std::unordered_map<std::string, 
		std::unordered_map<int, std::shared_ptr<olc::Font>>> _fonts;
};

#define FT Fonts::get()

} // namespace stemaj

#endif //__ASSETS_HPP