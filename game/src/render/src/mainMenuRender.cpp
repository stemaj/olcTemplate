#include <olcTemplate/game/src/render/mainMenuRender.hpp>
#include <olcTemplate/game/src/state/mainMenuState.hpp>
#include <olcTemplate/game/src/engine/olcPixelGameEngine.h>
#include <olcTemplate/game/assets.hpp>

using namespace stemaj;

void MainMenuRender::DoRender(olc::PixelGameEngine* pge, float fElapsedTime, State* state)
{
  auto mainMenu = static_cast<MainMenuState*>(state);

  pge->Clear(olc::DARK_BLUE);

  pge->DrawStringDecal(olc::vi2d{mainMenu->_headerPos.x, mainMenu->_headerPos.y},
    mainMenu->_headerText,
    olc::Pixel(int(mainMenu->_headerColor[0]*255.0f),
              int(mainMenu->_headerColor[1]*255.0f),
              int(mainMenu->_headerColor[2]*255.0f),
              int(mainMenu->_headerColor[3]*255.0f)));

  pge->DrawDecal({150,150}, AS.Decal("japan_1"), {0.2f,0.2f});
}
