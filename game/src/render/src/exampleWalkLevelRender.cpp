#include "game/assets.hpp"
#include <game/src/render/exampleWalkLevelRender.hpp>
#include <game/src/state/exampleWalkLevelState.hpp>
#include <game/src/engine/olcPixelGameEngine.h>

using namespace stemaj;

void ExampleWalkLevelRender::DoRender(olc::PixelGameEngine* pge, float fElapsedTime, State* state)
{
  auto walkLevel = static_cast<ExampleWalkLevelState*>(state);
  
  pge->DrawPartialDecal({(float)walkLevel->_drawPos.x, (float)walkLevel->_drawPos.y},
    AS.Renderable("bik")->Decal(),
    {(float)walkLevel->_sourceRectPos.x,(float)walkLevel->_sourceRectPos.y},
    {(float)walkLevel->_sourceRectSize.x,(float)walkLevel->_sourceRectPos.y},
    {walkLevel->_scale.x,walkLevel->_scale.y});
}
