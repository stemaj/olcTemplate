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

  auto font = FT.Font("CutiePatootie-Rgjv", Fontsize::NORMAL);
  auto r = font->RenderStringToDecal(
    utf8::utf8to32(std::string(screenElementsLevel->_text)), olc::WHITE);
  pge->DrawDecal({ (float)screenElementsLevel->_boxUpperLeft.x,
    (float)screenElementsLevel->_boxUpperLeft.y },
    r,{1.0f,1.0f});
}
