#include "game/src/engine/olcPGEX_TTF.h"
#include <game/src/render/exampleWalkLevelRender.hpp>
#include <game/src/state/exampleWalkLevelState.hpp>
#include <game/src/engine/olcPixelGameEngine.h>
#include <game/fonts.hpp>
#define UTF_CPP_CPLUSPLUS 202002L
#include <sdk/utfcpp/utf8.h>
#include <string>

using namespace stemaj;

void ExampleWalkLevelRender::DoRender(olc::PixelGameEngine* pge, float fElapsedTime, State* state)
{
  auto walkLevel = static_cast<ExampleWalkLevelState*>(state);

  pge->DrawPartialDecal({(float)walkLevel->_drawPos.x, (float)walkLevel->_drawPos.y},
    walkLevel->_decal,
    {(float)walkLevel->_sourceRectPos.x,(float)walkLevel->_sourceRectPos.y},
    {(float)walkLevel->_sourceRectSize.x,(float)walkLevel->_sourceRectSize.y},
    {walkLevel->_scale.x,walkLevel->_scale.y});

  auto font = FT.Font("CutiePatootie-Rgjv", 40);
  font->DrawString(utf8::utf8to32(std::string("Ä Bik ß")),200,80,olc::GREEN);
}
