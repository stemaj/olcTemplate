#ifndef __MAINMENURENDER_HPP
#define __MAINMENURENDER_HPP

#include <olcTemplate/game/gui.hpp>
#include <olcTemplate/game/src/render/render.hpp>
#include <olcTemplate/game/input.hpp>
#include <memory>

namespace olc {
  class Renderable;  
}

namespace stemaj {

class MainMenuRender : public Render
{
public:
	void DoRender(olc::PixelGameEngine* pge, float fElapsedTime, State* state) override;
  void Fade(olc::PixelGameEngine* pge, State* state) override final {}

private:
  std::vector<std::shared_ptr<olc::Renderable>> rends;

  std::shared_ptr<Gui> _gui;
};

} // namespace stemaj

#endif //__MAINMENURENDER_HPP
