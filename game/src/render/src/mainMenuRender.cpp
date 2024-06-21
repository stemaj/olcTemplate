#include <olcTemplate/game/src/render/mainMenuRender.hpp>
#include <olcTemplate/game/src/state/mainMenuState.hpp>
#include <olcTemplate/game/src/engine/olcPixelGameEngine.h>
#include <olcTemplate/game/src/engine/olcPGEX_TTF.h>
#include <olcTemplate/game/assets.hpp>
#include <olcTemplate/game/fonts.hpp>
#define UTF_CPP_CPLUSPLUS 202002L
#include <olcTemplate/sdk/utfcpp/utf8.h>

using namespace stemaj;

void MainMenuRender::DoRender(olc::PixelGameEngine* pge, float fElapsedTime, State* state)
{
  auto mainMenu = static_cast<MainMenuState*>(state);

  pge->Clear(olc::DARK_BLUE);

  for (const auto& g : mainMenu->_graphics)
  {
    auto a = CO.D({g.pos[0],g.pos[1]});
    pge->DrawDecal({(float)a.x,(float)a.y} , AS.Decal(g.name), {g.scale[0], g.scale[1]});
  }

  auto fontNormal = FT.Font(mainMenu->_font, FontSize::SMALLER);
  for (const auto& t : mainMenu->_texts)
  {
    auto a = CO.D({t.pos[0],t.pos[1]});

    olc::Decal* r = nullptr;
    r = fontNormal->RenderStringToDecal(utf8::utf8to32(std::string(t.text)), olc::Pixel(int(mainMenu->_headerColor[0]*255.0f),
                int(mainMenu->_headerColor[1]*255.0f),
                int(mainMenu->_headerColor[2]*255.0f),
                int(mainMenu->_headerColor[3]*255.0f)));
    pge->DrawDecal({(float)a.x, (float)a.y}, r);
  }
}
