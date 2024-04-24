#ifndef __FONTS_HPP
#define __FONTS_HPP

#include <unordered_map>
#include <memory>

namespace olc {
  class Font;
}

namespace stemaj {

class Fonts
{
public:

	static Fonts& get();
	Fonts(Fonts const&) = delete;
	void operator=(Fonts const&) = delete;

  olc::Font* Font(const std::string& name, const int fontSize);
  
  void Load();

private:
	Fonts() {}
	virtual ~Fonts() {}	

  std::unordered_map<std::string, 
		std::unordered_map<int, std::shared_ptr<olc::Font>>> _fonts;
};

#define FT Fonts::get()

} // namespace stemaj

#endif //__ASSETS_HPP