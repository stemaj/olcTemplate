#include <game/src/render/exampleScreenElementsLevelRender.hpp>
#include <game/src/state/exampleScreenElementsLevelState.hpp>
#include <game/src/engine/olcPixelGameEngine.h>
#include <game/src/engine/olcPGEX_TTF.h>
#include <game/fonts.hpp>
#define UTF_CPP_CPLUSPLUS 202002L
#include <sdk/utfcpp/utf8.h>

using namespace stemaj;

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
}
