#ifndef __ASSETS_HPP
#define __ASSETS_HPP

#include <game/src/engine/olcPixelGameEngine.h>

namespace stemaj {

class Assets
{
public:

	static Assets& get();
	Assets(Assets const&) = delete;
	void operator=(Assets const&) = delete;

  olc::Sprite* Sprite(const std::string& name);
  olc::Decal* Decal(const std::string& name);
  
  void Load();

private:
	Assets() {}
	virtual ~Assets() {}	

  std::map<std::string, std::pair<std::unique_ptr<olc::Sprite>, 
                                  std::unique_ptr<olc::Decal>>> _sprites;
};

#define AS Assets::get()

} // namespace stemaj

#endif //__ASSETS_HPP