#ifndef __ANIMATION_HPP
#define __ANIMATION_HPP

#include <olcTemplate/game/coordinates.hpp>
#include <olcTemplate/game/src/engine/olcUTIL_Geometry2D.h>
#include <olcTemplate/game/src/engine/olcUTIL_Animate2D.h>
#include <cstdint>
#include <string>
#include <unordered_map>

namespace stemaj {

enum AnimationKind : uint8_t
{
  IDLE = 0,
  MOVERIGHT = 1,
  MOVEUP = 2,
  MOVELEFT = 3,
  MOVEDOWN = 4,
  IDLE_LEFT = 5,
  NIGHT = 6,
  DOOR = 7,
  ROTATING = 8,
  WIND = 9,
  COUNT = 10
};

struct Animation
{
  int spriteWidth = 0;
  int spriteHeight = 0;
  float ox = 0.0f;
  float oy = 0.0f;
  olc::utils::Animate2D::Animation<AnimationKind> animation;
};

struct Sheet
{
  bool initialized = false;
  PT<float> pos = {0.0f,0.0f};
  olc::Decal* decal = nullptr;
  PT<float> sourceRectPos = {0.0f,0.0f};
  PT<float> sourceRectSize = {0.0f,0.0f};
  PT<float> scale = {0.0f,0.0f};
  AnimationKind currentKind = AnimationKind::IDLE;
  stemaj::Animation asset;
  olc::utils::Animate2D::AnimationState animationState = {};
};

class AnimationMap
{
public:
	static AnimationMap& get();
	AnimationMap(AnimationMap const&) = delete;
	void operator=(AnimationMap const&) = delete;

  stemaj::Animation& GetAnimation(const std::string& name);

  void Load();
  bool Loaded = false;
private:
	AnimationMap() {}
	virtual ~AnimationMap() {}	

  void LoadFrom(const std::string& path);

  std::unordered_map<std::string, stemaj::Animation> _map;
};

#define AN AnimationMap::get()
  
} // namespace stemaj

#endif // __ANIMATION_HPP
