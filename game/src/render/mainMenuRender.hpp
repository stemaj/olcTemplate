#ifndef __MAINMENURENDER_HPP
#define __MAINMENURENDER_HPP

#include <olcTemplate/game/src/render/render.hpp>

namespace stemaj {

class MainMenuRender : public Render
{
public:
  void DoRender(olc::PixelGameEngine* pge, float fElapsedTime, State* state) override;
  void Fade(olc::PixelGameEngine* pge, State* state) override final {}
};

} // namespace stemaj

#endif //__MAINMENURENDER_HPP