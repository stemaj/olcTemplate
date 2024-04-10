#include <game/src/render/examplePathLevelRender.hpp>
#include <game/src/state/examplePathLevelState.hpp>
#include <game/src/engine/olcPixelGameEngine.h>

using namespace stemaj;

void ExamplePathLevelRender::DoRender(olc::PixelGameEngine* pge, float fElapsedTime, State* state)
{
  auto pathLevel = static_cast<ExamplePathLevelState*>(state);

  pge->Clear(olc::DARK_GREY);
}