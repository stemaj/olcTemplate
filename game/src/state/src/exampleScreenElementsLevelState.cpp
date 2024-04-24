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