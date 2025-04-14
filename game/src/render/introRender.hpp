#ifndef __INTRORENDER_HPP
#define __INTRORENDER_HPP

#include "olcTemplate/game/src/engine/olcPGEX_TTF.h"
#include <memory>
#include <olcTemplate/game/src/render/render.hpp>
#include <vector>

namespace olc {
  class Renderable;
}

namespace stemaj {

class IntroRender : public Render
{
public:
  void DoRender(olc::PixelGameEngine* pge, float fElapsedTime, State* state) override;
  void Fade(olc::PixelGameEngine* pge, State* state) override final;

private:
  std::vector<std::shared_ptr<olc::Renderable>> rends;
};

} // namespace stemaj

#endif //__INTRORENDER_HPP