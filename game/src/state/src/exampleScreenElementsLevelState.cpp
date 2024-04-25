#include "game/fonts.hpp"
#include <algorithm>
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
  auto boxSize = FT.BoxSize(_text, FT.Font("CutiePatootie-Rgjv", Fontsize::NORMAL));
  _frameboxSize = { boxSize.x + 20, boxSize.y + 20 };
  
  _frameboxUpperLeft = { input.mouseX - _frameboxSize.x / 2, input.mouseY - _frameboxSize.y / 2};
  _frameboxUpperLeft = { std::clamp(_frameboxUpperLeft.x, 0, CO.W-_frameboxSize.x),
    std::clamp(_frameboxUpperLeft.y, 0, CO.H-_frameboxSize.y) } ;

  _boxUpperLeft = { _frameboxUpperLeft.x + 10, _frameboxUpperLeft.y + 10 };

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