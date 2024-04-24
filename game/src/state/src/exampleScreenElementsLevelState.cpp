#include "game/fonts.hpp"
#include <game/src/state/exampleScreenElementsLevelState.hpp>
#include <game/src/render/exampleScreenElementsLevelRender.hpp>
#include <game/src/render/levelRender.hpp>

using namespace stemaj;

ExampleScreenElementsLevelState::ExampleScreenElementsLevelState() : _render(std::make_unique<ExampleScreenElementsLevelRender>())
{
  LoadLevelData();
}

ExampleScreenElementsLevelState::~ExampleScreenElementsLevelState()
{
  SaveLevelData();
}

std::optional<std::unique_ptr<State>> ExampleScreenElementsLevelState::ExampleScreenElementsLevelState::Update(
  const Input& input, float fElapsedTime)
{
  _mousePos = {input.mouseX,input.mouseY };
  _boxSize = FT.BoxSize(_text, FT.Font("CutiePatootie-Rgjv", Fontsize::NORMAL));
  _boxUpperLeft = { input.mouseX - _boxSize.x / 2, input.mouseY - _boxSize.y / 2};

  return std::nullopt;
}

Render* ExampleScreenElementsLevelState::GetRender()
{
  return _render.get();
}

void ExampleScreenElementsLevelState::LoadLevelData()
{
  std::cout << "loading" << std::endl;
}

void ExampleScreenElementsLevelState::SaveLevelData()
{
  std::cout << "saving" << std::endl;
}