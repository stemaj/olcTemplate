#include <olcTemplate/game/src/render/logoRender.hpp>
#include <olcTemplate/game/src/state/logoState.hpp>
#include <olcTemplate/game/src/engine/olcPixelGameEngine.h>
#include <olcTemplate/game/assets.hpp>

using namespace stemaj;

void LogoRender::DoRender(olc::PixelGameEngine* pge, float fElapsedTime, State* state)
{
  auto intro = static_cast<LogoState*>(state);

  pge->Clear(olc::WHITE);

  if (!intro->loaded)
  {
    return;
  }

  pge->DrawPartialDecal({(float)intro->_bgDrawPos.x, (float)intro->_bgDrawPos.y},
  intro->_bgDecal,
  {(float)intro->_bgSourceRectPos.x,(float)intro->_bgSourceRectPos.y},
  {(float)intro->_bgSourceRectSize.x,(float)intro->_bgSourceRectSize.y},
  {intro->_bgScale.x,intro->_bgScale.y});
}

void LogoRender::Fade(olc::PixelGameEngine* pge, State* state)
{
  // auto logo = static_cast<LogoState*>(state);

  // if (logo->_fader.IsFading() || logo->_fader.IsTurning())
  // {
  //   pge->FillRectDecal({0,0},pge->GetScreenSize(),
  //     olc::Pixel(0,0,0,logo->_fader.GetAlpha()));
  // }
}
