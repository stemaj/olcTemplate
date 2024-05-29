#include <olcTemplate/game/src/render/mainMenuRender.hpp>
#include <olcTemplate/game/src/state/mainMenuState.hpp>
#include <olcTemplate/game/src/engine/olcPixelGameEngine.h>
#include <olcTemplate/game/assets.hpp>

using namespace stemaj;

void MainMenuRender::DoRender(olc::PixelGameEngine* pge, float fElapsedTime, State* state)
{
  auto mainMenu = static_cast<MainMenuState*>(state);

  pge->Clear(olc::DARK_BLUE);

  pge->DrawStringDecal(olc::vi2d{mainMenu->someX, mainMenu->someY},
    mainMenu->someText,
    olc::Pixel(int(mainMenu->someColor[0]*255.0f),
              int(mainMenu->someColor[1]*255.0f),
              int(mainMenu->someColor[2]*255.0f),
              int(mainMenu->someColor[3]*255.0f)));

  pge->DrawDecal({150,150}, AS.Decal("japan_1"), {0.2f,0.2f});
}
