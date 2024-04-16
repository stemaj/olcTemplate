#include <game/src/state/exampleWalkLevelState.hpp>
#include <game/src/render/exampleWalkLevelRender.hpp>
#include <game/src/render/levelRender.hpp>

using namespace stemaj;

ExampleWalkLevelState::ExampleWalkLevelState() : _render(std::make_unique<ExampleWalkLevelRender>())
{
  LoadLevelData();
}

ExampleWalkLevelState::~ExampleWalkLevelState()
{
  SaveLevelData();
}

std::optional<std::unique_ptr<State>> ExampleWalkLevelState::ExampleWalkLevelState::Update(
  const Input& input, float fElapsedTime)
{
  return std::nullopt;
}

Render* ExampleWalkLevelState::GetRender()
{
  return _render.get();
}

void ExampleWalkLevelState::LoadLevelData()
{
  std::cout << "loading" << std::endl;
}

void ExampleWalkLevelState::SaveLevelData()
{
  std::cout << "saving" << std::endl;
}