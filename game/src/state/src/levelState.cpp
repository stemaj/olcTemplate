#include <game/src/state/levelState.hpp>
#include "game/src/render/levelRender.hpp"
#include <game/src/state/exampleWalkLevelState.hpp>
#include <memory>
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
  return std::make_unique<ExampleWalkLevelState>();
}
