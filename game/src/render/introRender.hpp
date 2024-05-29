#ifndef __INTRORENDER_HPP
#define __INTRORENDER_HPP

#include <olcTemplate/game/src/render/render.hpp>

namespace stemaj {

class IntroRender : public Render
{
public:
  void DoRender(olc::PixelGameEngine* pge, float fElapsedTime, State* state) override;
  void Fade(olc::PixelGameEngine* pge, State* state) override final {}
};

} // namespace stemaj

#endif //__INTRORENDER_HPP