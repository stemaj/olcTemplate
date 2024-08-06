#ifndef __LOGORENDER_HPP
#define __LOGORENDER_HPP

#include <olcTemplate/game/src/render/render.hpp>

namespace stemaj {

class LogoRender : public Render
{
public:
  void DoRender(olc::PixelGameEngine* pge, float fElapsedTime, State* state) override;
  void Fade(olc::PixelGameEngine* pge, State* state) override final;
};

} // namespace stemaj

#endif //__LOGORENDER_HPP