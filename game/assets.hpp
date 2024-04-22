#ifndef __ASSETS_HPP
#define __ASSETS_HPP

#include <cstdint>
#include <string>
#include <memory>
#include <unordered_map>

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
struct AnimationContainer
{
  int spriteWidth = 0;
  int spriteHeight = 0;
  float ox = 0.0f;
  float oy = 0.0f;
  std::unordered_map<AnimationKind, std::unique_ptr<olc::utils::Animate2D::Animation<AnimationKind>>> animation = {};
};

class Assets
{
public:

	static Assets& get();
	Assets(Assets const&) = delete;
	void operator=(Assets const&) = delete;

  olc::Sprite* Sprite(const std::string& name);
  olc::Decal* Decal(const std::string& name);
  olc::Renderable* Renderable(const std::string& name);
  AnimationContainer* Animation(const std::string& name);
  
  void Load();

private:
	Assets() {}
	virtual ~Assets() {}	

  std::unordered_map<std::string, std::unique_ptr<olc::Sprite>> _sprites;
  std::unordered_map<std::string, std::unique_ptr<olc::Decal>> _decals;
  std::unordered_map<std::string, std::unique_ptr<olc::Renderable>> _renderables;
  std::unordered_map<std::string, std::unique_ptr<AnimationContainer>> _animationContainers;
};

#define AS Assets::get()

} // namespace stemaj

#endif //__ASSETS_HPP