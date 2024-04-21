#ifndef __ASSETS_HPP
#define __ASSETS_HPP

#include <cstdint>
#include <string>
#include <memory>
#include <map>
#include <unordered_map>
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

enum AnimationKind : uint8_t
{
  IDLE = 0,
  MOVERIGHT = 1,
  MOVEUP = 2,
  MOVELEFT = 3,
  MOVEDOWN = 4,
  COUNT
};
struct AnimationDetail
{
  std::vector<std::pair<int,int>> singlePics;
  olc::utils::Animate2D::Animation<AnimationKind>* animation = nullptr;
};
struct AnimationContainer
{
  int spriteWidth = 0;
  int spriteHeight = 0;
  float ox = 0.0f;
  float oy = 0.0f;
  std::unordered_map<AnimationKind, AnimationDetail> details;
};

class Assets
{
public:

	static Assets& get();
	Assets(Assets const&) = delete;
	void operator=(Assets const&) = delete;

  olc::Sprite* Sprite(const std::string& name);
  olc::Decal* Decal(const std::string& name);
  AnimationContainer* AnimatedSprite(const std::string& name);
  
  void Load();

private:
	Assets() {}
	virtual ~Assets() {}	

  std::map<std::string, std::pair<std::unique_ptr<olc::Sprite>, 
                                  std::unique_ptr<olc::Decal>>> _sprites;
  std::map<std::string, std::pair<std::unique_ptr<AnimationContainer>,
                                  std::unique_ptr<olc::Renderable>>> _animatedSprites;
};

#define AS Assets::get()

} // namespace stemaj

#endif //__ASSETS_HPP