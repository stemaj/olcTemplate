#include "game/src/render/mainMenuRender.hpp"
#include <game/src/state/mainMenuState.hpp>
#include <memory>

using namespace stemaj;

MainMenuState::MainMenuState() : _render(std::make_unique<MainMenuRender>())
{
}

Render* MainMenuState::GetRender()
{
  return _render.get();
}

void MainMenuState::Update(const Input& input)
{
  if (input.leftMouseClicked)
  {
    someColor = someColor == "white" ? "red" : "white";
  }
}
