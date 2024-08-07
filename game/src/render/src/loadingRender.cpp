#include <olcTemplate/game/src/render/loadingRender.hpp>
#include <olcTemplate/game/src/state/loading.hpp>
#include <olcTemplate/game/src/engine/olcPixelGameEngine.h>
#include <olcTemplate/game/assets.hpp>

using namespace stemaj;

void LoadingRender::DoRender(olc::PixelGameEngine* pge, float fElapsedTime, State* state)
{
  pge->Clear(olc::WHITE);
  pge->DrawStringDecal({10,10}, "Loading...", olc::BLACK);
}

void LoadingRender::Fade(olc::PixelGameEngine* pge, State* state)
{
}
