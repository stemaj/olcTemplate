#ifndef __ASSETS_HPP
#define __ASSETS_HPP

#include <cstdint>
#include <string>
#include <memory>
#include <map>
#include <vector>

namespace olc {
  class Sprite;
  class Decal;
  class Renderable;
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
  struct AnimationDetails
  {
    AnimationKind kind = IDLE;
    olc::utils::Animate2D::Animation<AnimationKind>* animation = nullptr;
    int spriteWidth = 0;
    int spriteHeight = 0;
    float ox = 0.0f;
    float oy = 0.0f;
    std::vector<std::pair<int,int>> singlePics;
  };

  olc::Sprite* Sprite(const std::string& name);
  olc::Decal* Decal(const std::string& name);
  AnimationDetails AnimatedSprite(const std::string& name);
  
  void Load();

private:
	Assets() {}
	virtual ~Assets() {}	

  std::map<std::string, std::pair<std::unique_ptr<olc::Sprite>, 
                                  std::unique_ptr<olc::Decal>>> _sprites;
  std::map<std::string, std::pair<std::unique_ptr<olc::utils::Animate2D::Animation<AnimationKind>>,
                                  std::unique_ptr<olc::Renderable>>> _animatedSprites;
};

#define AS Assets::get()

} // namespace stemaj

#endif //__ASSETS_HPP