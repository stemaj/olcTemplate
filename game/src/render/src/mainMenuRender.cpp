#include <game/src/render/mainMenuRender.hpp>
#include <game/src/state/mainMenuState.hpp>
#include <game/src/engine/olcPixelGameEngine.h>

using namespace stemaj;

void MainMenuRender::DoRender(olc::PixelGameEngine* pge, float fElapsedTime, State* state)
{
  auto mainMenu = static_cast<MainMenuState*>(state);

  pge->Clear(olc::DARK_BLUE);

  pge->DrawStringDecal(olc::vi2d{mainMenu->someX, mainMenu->someY},
    mainMenu->someText,
    mainMenu->someColor == "white" ? olc::WHITE : olc::RED);
}
