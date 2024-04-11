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

  for (auto g : pathLevel->DisplayGrid)
  {
    pge->DrawCircle({g.x,g.y},1,toPixelColor(pathLevel->_colorPath));
  }

  pge->DrawCircle({pathLevel->DisplayStart.x, pathLevel->DisplayStart.y},
    3, toPixelColor(pathLevel->_colorStart));
}