#include <olcTemplate/game/src/render/introRender.hpp>
#include <olcTemplate/game/src/state/introState.hpp>
#include <olcTemplate/game/src/engine/olcPixelGameEngine.h>
#include <olcTemplate/game/assets.hpp>
#include <olcTemplate/game/fonts.hpp>
#include <olcTemplate/game/src/engine/olcPGEX_TTF.h>
#define UTF_CPP_CPLUSPLUS 202002L
#include <olcTemplate/sdk/utfcpp/utf8.h>
#include <string>

using namespace stemaj;

void IntroRender::DoRender(olc::PixelGameEngine* pge, float fElapsedTime, State* state)
{
  auto intro = static_cast<IntroState*>(state);

  pge->Clear(olc::DARK_YELLOW);

  pge->DrawPartialDecal({(float)intro->_bgDrawPos.x, (float)intro->_bgDrawPos.y},
  intro->_bgDecal,
  {(float)intro->_bgSourceRectPos.x,(float)intro->_bgSourceRectPos.y},
  {(float)intro->_bgSourceRectSize.x,(float)intro->_bgSourceRectSize.y},
  {intro->_bgScale.x,intro->_bgScale.y});

  pge->DrawPartialDecal({(float)intro->_chDrawPos.x, (float)intro->_chDrawPos.y},
  intro->_chDecal,
  {(float)intro->_chSourceRectPos.x,(float)intro->_chSourceRectPos.y},
  {(float)intro->_chSourceRectSize.x,(float)intro->_chSourceRectSize.y},
  {intro->_chScale.x,intro->_chScale.y});

  const std::string fontName = "dogica";
  auto fontNormal = FT.Font(fontName, FontSize::SMALLER);
  auto fontBig = FT.Font(fontName, FontSize::SMALL);
  auto fontBigger = FT.Font(fontName, FontSize::NORMAL);

  olc::Decal* r = nullptr;

  auto t = CO.D(PT<float>{0.05f,0.8f});
  switch (intro->_part)
  {
  case IntroState::Parts::OLCLOGO:
    {
      auto d = CO.D(PT<float>{0.03f,0.8f});
      float scale = 0.7f * CO.W / AS.Sprite("pge2_logo")->width;
      pge->DrawDecal({(float)d.x, (float)d.y}, AS.Decal("pge2_logo"), {scale,scale});
    }
    break;
  case IntroState::Parts::RIEGEL:
    r = fontBig->RenderStringToDecal(utf8::utf8to32(std::string("Riegel")), olc::WHITE);
    pge->DrawDecal({ (float)t.x, (float)t.y }, r);
    break;
  case IntroState::Parts::DADDY:
    r = fontBig->RenderStringToDecal(utf8::utf8to32(std::string("Daddy Daddy")), olc::WHITE);
    pge->DrawDecal({ (float)t.x, (float)t.y }, r);
    break;
  case IntroState::Parts::VFC:
    r = fontBig->RenderStringToDecal(utf8::utf8to32(std::string("Volcano Fish Cat")), olc::WHITE);
    pge->DrawDecal({ (float)t.x, (float)t.y }, r);
    break;
  case IntroState::Parts::GAME:
    {
      auto p1 = CO.D(PT<float>{0.05f,0.2f});
      r = fontBigger->RenderStringToDecal(utf8::utf8to32(std::string("Name of the game")), olc::WHITE);
      pge->DrawDecal({ (float)p1.x, (float)p1.y }, r);
      auto p2 = CO.D(PT<float>{0.05f,0.85f});
      r = fontNormal->RenderStringToDecal(utf8::utf8to32(std::string("(c) 2024 riegel games")), olc::WHITE);
      pge->DrawDecal({ (float)p2.x, (float)p2.y }, r);
    }
  case IntroState::Parts::BLACK:
    break;
  }
}

void IntroRender::Fade(olc::PixelGameEngine* pge, State* state)
{
  auto intro = static_cast<IntroState*>(state);

  if (intro->_fader.IsFading() || intro->_fader.IsTurning())
  {
    pge->FillRectDecal({0,0},pge->GetScreenSize(),
      olc::Pixel(0,0,0,intro->_fader.GetAlpha()));
  }
}
