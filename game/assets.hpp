#ifndef __ASSETS_HPP
#define __ASSETS_HPP

#include <string>
#include <memory>
#include <map>

namespace olc {
  class Sprite;
  class Decal;
  namespace utils {
    namespace Animate2D {
      template<typename StatesEnum>
      class Animation;
    }
  }
}

namespace stemaj {

class Assets
{
public:

	static Assets& get();
	Assets(Assets const&) = delete;
	void operator=(Assets const&) = delete;

  enum AnimationKind : uint8_t
	{
    IDLE = 0,
    MOVERIGHT = 1,
    MOVEUP = 2,
    MOVELEFT = 3,
    MOVEDOWN = 4
	};

  olc::Sprite* Sprite(const std::string& name);
  olc::Decal* Decal(const std::string& name);
  olc::utils::Animate2D::Animation<AnimationKind>* AnimatedSprite(const std::string& name);
  
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