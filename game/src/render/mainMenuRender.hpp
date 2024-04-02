#ifndef __MAINMENURENDER_HPP
#define __MAINMENURENDER_HPP

#include <game/input.hpp>
#include <game/src/render/render.hpp>

namespace stemaj {

class Render;

class MainMenuRender : public Render
{
public:
  void DoRender(olc::PixelGameEngine* pge, float fElapsedTime, State* state) override;
};

} // namespace stemaj

#endif //__MAINMENURENDER_HPP