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

  auto fontNormal = FT.Font(intro->_font, FontSize::SMALLER);
  auto fontBig = FT.Font(intro->_font, FontSize::SMALL);
  auto fontBigger = FT.Font(intro->_font, FontSize::NORMAL);

  olc::Decal* r = nullptr;

  auto color = olc::Pixel(int(intro->_headerColor[0]*255.0f),
                int(intro->_headerColor[1]*255.0f),
                int(intro->_headerColor[2]*255.0f),
                int(intro->_headerColor[3]*255.0f));

  switch (intro->_part)
  {
  case IntroState::Parts::OLCLOGO:
    {
      float scale = 0.7f * CO.W / AS.Sprite("pge2_logo")->width;
      auto d = CO.D(intro->_olcLogoPos);
      pge->DrawDecal({(float)d.x, (float)d.y}, AS.Decal("pge2_logo"), {scale,scale});
    }
    break;
  case IntroState::Parts::RIEGEL:
    {
      r = fontBig->RenderStringToDecal(utf8::utf8to32(std::string("RIEGEL")), color);
      auto t = CO.D(intro->_riegelPos);
      pge->DrawDecal({ (float)t.x, (float)t.y }, r);
    }
    break;
  case IntroState::Parts::DADDY:
    {
      r = fontBig->RenderStringToDecal(utf8::utf8to32(std::string("DADDY DADDY")), color);
      auto t = CO.D(intro->_daddyPos);
      pge->DrawDecal({ (float)t.x, (float)t.y }, r);
    }
    break;
  case IntroState::Parts::VFC:
    {
      r = fontBig->RenderStringToDecal(utf8::utf8to32(std::string("VOLCANO FISH CAT")), color);
      auto t = CO.D(intro->_vfcPos);
      pge->DrawDecal({ (float)t.x, (float)t.y }, r);
    }
    break;
  case IntroState::Parts::GAME:
    {
      auto p1 = CO.D(intro->_nameOfTheGamePos);
      r = fontBigger->RenderStringToDecal(utf8::utf8to32(std::string(intro->_nameOfTheGame)), color);
      pge->DrawDecal({ (float)p1.x, (float)p1.y }, r);
      auto p2 = CO.D(intro->_copyrightPos);
      r = fontNormal->RenderStringToDecal(utf8::utf8to32(std::string(intro->_copyright)), color);
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
