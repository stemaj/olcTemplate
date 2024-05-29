#include <olcTemplate/game/src/render/introRender.hpp>
#include <olcTemplate/game/src/state/introState.hpp>
#include <olcTemplate/game/src/engine/olcPixelGameEngine.h>
#include <olcTemplate/game/assets.hpp>

using namespace stemaj;

void IntroRender::DoRender(olc::PixelGameEngine* pge, float fElapsedTime, State* state)
{
  auto mainMenu = static_cast<IntroState*>(state);

  pge->Clear(olc::DARK_YELLOW);

  pge->DrawDecal({0,0}, AS.Decal("japan_1"), {0.4f,0.4f});
}
