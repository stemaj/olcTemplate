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
  auto m = static_cast<MainMenuState*>(state);

  pge->Clear(olc::DARK_BLUE);

  for (const auto& g : m->_graphics)
  {
    pge->DrawDecal({ (float)g.pos.x, (float)g.pos.y }, AS.Decal(g.file), {g.scale, g.scale});
  }

  auto fontNormal = FT.Font(m->_font, FontSize::SMALLER);
  for (const auto& t : m->_texts)
  {
    olc::Decal* r = nullptr;
    r = fontNormal->RenderStringToDecal(
      utf8::utf8to32(std::string(t.text)),
      olc::Pixel(m->_colors[t.colorListIndex][0],
        m->_colors[t.colorListIndex][1],
        m->_colors[t.colorListIndex][2],
        m->_colors[t.colorListIndex][3]));
    pge->DrawDecal({(float)t.pos.x, (float)t.pos.y}, r);
  }
}
