#include <game/src/state/levelState.hpp>
#include "game/src/render/levelRender.hpp"
//#include <game/src/state/exampleCollisionState.hpp>
//#include <game/src/state/examplePathLevelState.hpp>
//#include <game/src/state/exampleWalkLevelState.hpp>
#include <game/src/state/exampleScreenElementsLevelState.hpp>
#include <optional>
#include <sdk/imgui-1.90.4/imgui.h>

using namespace stemaj;

LevelState::LevelState() : _render(std::make_unique<LevelRender>())
{
}

Render* LevelState::GetRender()
{
  return _render.get();
}

std::optional<std::unique_ptr<State>> LevelState::Update(const Input& input, float fElapsedTime)
{
  //  return std::make_unique<ExampleCollisionState>();
  //  return std::make_unique<ExamplePathLevelState>();
  //  return std::make_unique<ExampleWalkLevelState>();
  return std::make_unique<ExampleScreenElementsLevelState>();

}
