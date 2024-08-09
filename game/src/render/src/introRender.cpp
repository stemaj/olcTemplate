#include <olcTemplate/game/src/render/introRender.hpp>
#include <olcTemplate/game/src/state/introState.hpp>
#include <olcTemplate/game/src/engine/olcPixelGameEngine.h>
#include <olcTemplate/game/assets.hpp>
#include <olcTemplate/game/fonts.hpp>
#include <olcTemplate/game/src/engine/olcPGEX_TTF.h>
#define UTF_CPP_CPLUSPLUS 202002L
#include <olcTemplate/sdk/utfcpp/utf8.h>

using namespace stemaj;

void IntroRender::DoRender(olc::PixelGameEngine* pge, float fElapsedTime, State* state)
{
  auto i = static_cast<IntroState*>(state);

  pge->Clear(olc::DARK_YELLOW);

  for (const auto& b : i->_sheets)
  {
    auto dPos = CO.D({b.pos.x,b.pos.y}).to<float>();
    pge->DrawPartialDecal(
      {dPos.x,dPos.y},
      b.decal,
      {b.sourceRectPos.x,b.sourceRectPos.y},
      {b.sourceRectSize.x,b.sourceRectSize.y},
      {b.scale.x,b.scale.y}
    );
  }

  for (const auto& index : i->_activeGraphicIndicies)
  {
    auto g = i->_graphics[index];
    pge->DrawDecal(
      {(float)g.pos.x,(float)g.pos.y},
      AS.Decal(g.file),
      {g.scale,g.scale}
    );
  }

  for (const auto& index : i->_activeTextIndicies)
  {
    auto t = i->_texts[index];
    auto col = i->_colors[t.colorListIndex];
    auto font = FT.Font(i->_font, (FontSize)t.fontSize);
    pge->DrawDecal({(float)t.pos.x,(float)t.pos.y},
      font->RenderStringToDecal(
        utf8::utf8to32(t.text),
        olc::Pixel(col[0],col[1],col[2],col[3])
    ));
  }
}

void IntroRender::Fade(olc::PixelGameEngine* pge, State* state)
{
  auto intro = static_cast<IntroState*>(state);

  if (intro->_fader->IsFading() || intro->_fader->IsTurning())
  {
    pge->FillRectDecal({0,0},pge->GetScreenSize(),
      olc::Pixel(0,0,0,intro->_fader->GetAlpha()));
  }
}
