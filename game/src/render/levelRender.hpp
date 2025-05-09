#ifndef __LEVELRENDER_HPP
#define __LEVELRENDER_HPP

#include <olcTemplate/game/gui.hpp>
#include <olcTemplate/game/src/render/render.hpp>

namespace stemaj {

class LevelRender : public Render
{
public:
  LevelRender();

  void DoRender(olc::PixelGameEngine* pge, float fElapsedTime, State* state) override;
  void Fade(olc::PixelGameEngine* pge, State* state) override final;
protected:
  std::unique_ptr<Gui> _gui;
};

} // namespace stemaj

#endif //__LEVELRENDER_HPP