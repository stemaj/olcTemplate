#ifndef __ASSETS_HPP
#define __ASSETS_HPP

#include <string>
#include <memory>
#include <unordered_map>

namespace olc {
  class Sprite;
  class Decal;
  class Renderable;
  // namespace utils {
  //   namespace Animate2D {
  //     template<typename StatesEnum>
  //     class Animation;
  //   }
  // }
}

namespace stemaj {

class Assets
{
public:

	static Assets& get();
	Assets(Assets const&) = delete;
	void operator=(Assets const&) = delete;

  olc::Sprite* Sprite(const std::string& name);
  olc::Decal* Decal(const std::string& name);
  olc::Renderable* Renderable(const std::string& name);
  
  void Load();

private:
	Assets() {}
	virtual ~Assets() {}	

  std::unordered_map<std::string, std::unique_ptr<olc::Sprite>> _sprites;
  std::unordered_map<std::string, std::unique_ptr<olc::Decal>> _decals;
  std::unordered_map<std::string, std::unique_ptr<olc::Renderable>> _renderables;
};

#define AS Assets::get()

} // namespace stemaj

#endif //__ASSETS_HPP