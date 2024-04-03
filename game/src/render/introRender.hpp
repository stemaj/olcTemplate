#ifndef __INTRORENDER_HPP
#define __INTRORENDER_HPP

#include <game/src/render/render.hpp>

namespace stemaj {

class IntroRender : public Render
{
public:
  void DoRender(olc::PixelGameEngine* pge, float fElapsedTime, State* state) override;
};

} // namespace stemaj

#endif //__INTRORENDER_HPP