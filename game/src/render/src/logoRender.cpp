#include <olcTemplate/game/src/render/logoRender.hpp>
#include <olcTemplate/game/src/state/logoState.hpp>
#include <olcTemplate/game/src/engine/olcPixelGameEngine.h>
#include <olcTemplate/game/assets.hpp>

using namespace stemaj;

void LogoRender::DoRender(olc::PixelGameEngine* pge, float fElapsedTime, State* state)
{
  auto l = static_cast<LogoState*>(state);

  pge->Clear(olc::WHITE);

  pge->DrawPartialDecal({l->_logoSheet.pos.x, l->_logoSheet.pos.y},
    l->_logoSheet.decal,
    {l->_logoSheet.sourceRectPos.x,l->_logoSheet.sourceRectPos.y},
    {l->_logoSheet.sourceRectSize.x,l->_logoSheet.sourceRectSize.y},
    {l->_logoSheet.scale.x,l->_logoSheet.scale.y});
}

void LogoRender::Fade(olc::PixelGameEngine* pge, State* state)
{
  auto logo = static_cast<LogoState*>(state);

  if (logo->_fader.IsFading() || logo->_fader.IsTurning())
  {
    pge->FillRectDecal({0,0},pge->GetScreenSize(),
      olc::Pixel(0,0,0,logo->_fader.GetAlpha()));
  }
}
