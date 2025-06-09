#ifndef __RENDERCUTSCENE_HPP
#define __RENDERCUTSCENE_HPP

#include <olcTemplate/game/src/render/render.hpp>

namespace stemaj {

class RenderCutscene : public Render
{
public:
  void DoRender(olc::PixelGameEngine* pge, float fElapsedTime, State* state) override;
  void Fade(olc::PixelGameEngine* pge, State* state) override final;
};

} // namespace stemaj

#endif //__RENDERCUTSCENE_HPP