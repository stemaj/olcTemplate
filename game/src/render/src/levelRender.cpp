#include <olcTemplate/game/gui.hpp>
#include <olcTemplate/game/src/render/render.hpp>
#include <olcTemplate/game/src/render/levelRender.hpp>
#include <olcTemplate/game/src/state/levelState.hpp>
#include <olcTemplate/game/src/engine/olcPixelGameEngine.h>

using namespace stemaj;

LevelRender::LevelRender() : _gui(std::make_unique<Gui>())
{
  
}

void LevelRender::DoRender(olc::PixelGameEngine* pge, float fElapsedTime, State* state)
{
  pge->Clear(olc::RED);
}

void LevelRender::Fade(olc::PixelGameEngine* pge, State* state)
{
  auto level = static_cast<LevelState*>(state);

  if (level->_fader.IsFading() || level->_fader.IsTurning())
  {
    pge->FillRectDecal({0,0},pge->GetScreenSize(),
      olc::Pixel(0,0,0,level->_fader.GetAlpha()));
  }
}
