#include <game/src/render/exampleScreenElementsLevelRender.hpp>
#include <game/src/state/exampleScreenElementsLevelState.hpp>
#include <game/src/engine/olcPixelGameEngine.h>
#include <game/src/engine/olcPGEX_TTF.h>
#include <game/fonts.hpp>
#define UTF_CPP_CPLUSPLUS 202002L
#include <sdk/utfcpp/utf8.h>

using namespace stemaj;

olc::Renderable _r;
olc::Decal* GetLine()
{
  int w = 4, h = 1;
  _r.Create(w,h);
  for (int x = 0; x < w; x++)
    for (int y = 0; y < h; y++)
    {
      if (x < 1 || x > w-2)
        _r.Sprite()->SetPixel({x,y},olc::BLANK);
      else 
        _r.Sprite()->SetPixel({x,y},olc::GREEN);
    }
  _r.Decal()->Update();
  return _r.Decal();
}

void ExampleScreenElementsLevelRender::DoRender(olc::PixelGameEngine* pge, float fElapsedTime, State* state)
{
  auto screenElementsLevel = static_cast<ExampleScreenElementsLevelState*>(state);

  pge->Clear(olc::DARK_CYAN);

  pge->FillRectDecal( { (float)screenElementsLevel->_frameboxUpperLeft.x,
    (float)screenElementsLevel->_frameboxUpperLeft.y },
    { (float)screenElementsLevel->_frameboxSize.x, 
    (float)screenElementsLevel->_frameboxSize.y },
    olc::Pixel(235,242,244, 224) );

  auto font = FT.Font("CutiePatootie-Rgjv", Fontsize::NORMAL);
  auto textDecal = font->RenderStringToDecal(
    utf8::utf8to32(std::string(screenElementsLevel->_text)), olc::WHITE);
  pge->DrawDecal({ (float)screenElementsLevel->_boxUpperLeft.x,
      (float)screenElementsLevel->_boxUpperLeft.y },
    textDecal,{1.0f,1.0f});

  std::array<olc::vf2d, 4> points = {
    olc::vf2d{1,0},
    olc::vf2d{0,1},
    olc::vf2d{(float)screenElementsLevel->_mousePos.x-1,
      (float)screenElementsLevel->_mousePos.y},
    olc::vf2d{(float)screenElementsLevel->_mousePos.x,
      (float)screenElementsLevel->_mousePos.y-1}
  };
  
  pge->DrawWarpedDecal(GetLine(), points);
}
