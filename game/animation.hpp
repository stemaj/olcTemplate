#ifndef __ANIMATION_HPP
#define __ANIMATION_HPP

#include <cstdint>
#include <string>
#include <unordered_map>

#include <olcTemplate/game/src/engine/olcUTIL_Geometry2D.h>
#include <olcTemplate/game/src/engine/olcUTIL_Animate2D.h>



namespace stemaj {

enum AnimationKind : uint8_t
{
  IDLE = 0,
  MOVERIGHT = 1,
  MOVEUP = 2,
  MOVELEFT = 3,
  MOVEDOWN = 4,
  COUNT = 5
};

struct Animation
{
  int spriteWidth = 0;
  int spriteHeight = 0;
  float ox = 0.0f;
  float oy = 0.0f;
  olc::utils::Animate2D::Animation<AnimationKind> animation;
};

class AnimationMap
{
public:
	static AnimationMap& get();
	AnimationMap(AnimationMap const&) = delete;
	void operator=(AnimationMap const&) = delete;

  stemaj::Animation& GetAnimation(const std::string& name);

  void Load();
private:
	AnimationMap() {}
	virtual ~AnimationMap() {}	

  void LoadFrom(const std::string& path);

  std::unordered_map<std::string, stemaj::Animation> _map;
};

#define AN AnimationMap::get()
  
} // namespace stemaj

#endif // __ANIMATION_HPP
