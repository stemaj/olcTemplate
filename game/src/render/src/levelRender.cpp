#include <game/src/render/levelRender.hpp>
#include <game/src/state/levelState.hpp>
#include <game/src/engine/olcPixelGameEngine.h>

using namespace stemaj;

void LevelRender::DoRender(olc::PixelGameEngine* pge, float fElapsedTime, State* state)
{
  auto level = static_cast<LevelState*>(state);

  pge->Clear(olc::DARK_RED);
}