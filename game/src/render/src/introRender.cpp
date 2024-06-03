#include <olcTemplate/game/src/render/introRender.hpp>
#include <olcTemplate/game/src/state/introState.hpp>
#include <olcTemplate/game/src/engine/olcPixelGameEngine.h>
#include <olcTemplate/game/assets.hpp>

using namespace stemaj;

void IntroRender::DoRender(olc::PixelGameEngine* pge, float fElapsedTime, State* state)
{
  auto intro = static_cast<IntroState*>(state);

  pge->Clear(olc::DARK_YELLOW);

  switch (intro->_part)
  {
  case IntroState::Parts::OLCLOGO:
    pge->DrawStringDecal({10.0f, 180.0f}, "olc Pixel Game Engine");
    break;
  case IntroState::Parts::RIEGEL:
    pge->DrawStringDecal({10.0f, 180.0f}, "Riegel");
    break;
  case IntroState::Parts::DADDY:
    pge->DrawStringDecal({10.0f, 180.0f}, "Daddy Daddy");
    break;
  case IntroState::Parts::VFC:
    pge->DrawStringDecal({10.0f, 180.0f}, "Volcano Fish Cat");
    break;
  case IntroState::Parts::GAME:
    pge->DrawStringDecal({10.0f, 100.0f}, "OlcHello", olc::WHITE, {3.0f, 3.0f});
    pge->DrawStringDecal({10.0f, 190.0f}, "(c) 2024 riegel games", olc::WHITE, {0.5f, 0.5f});
  case IntroState::Parts::BLACK:
    break;
  }

  //pge->DrawDecal({0,0}, AS.Decal("japan_1"), {0.4f,0.4f});
}
