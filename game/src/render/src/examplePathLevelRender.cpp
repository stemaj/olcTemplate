#include <game/src/render/examplePathLevelRender.hpp>
#include <game/src/state/examplePathLevelState.hpp>
#include <game/src/engine/olcPixelGameEngine.h>

using namespace stemaj;

void ExamplePathLevelRender::DoRender(olc::PixelGameEngine* pge, float fElapsedTime, State* state)
{
  auto pathLevel = static_cast<ExamplePathLevelState*>(state);

  auto toPixelColor = [](const ExamplePathLevelState::Color& c){
    return olc::Pixel{ c.r, c.g, c.b, c.alpha };
  };

  pge->Clear(toPixelColor(pathLevel->_colorBackground));

  for (auto g : pathLevel->_displayGrid)
  {
    pge->DrawCircle({g.x,g.y},1,toPixelColor(pathLevel->_colorPath));
  }

  pge->DrawCircle({pathLevel->_displayStart.x, pathLevel->_displayStart.y},
    3, toPixelColor(pathLevel->_colorStart));

  pge->DrawCircle({pathLevel->_displayEnd.x, pathLevel->_displayEnd.y},
    3, toPixelColor(pathLevel->_colorEnd));
}
