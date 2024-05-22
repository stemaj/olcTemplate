#include <game/src/state/levelState.hpp>
#include "game/src/render/levelRender.hpp"
#include <game/src/state/exampleCollisionState.hpp>
#include <game/src/state/examplePathLevelState.hpp>
#include <game/src/state/exampleWalkLevelState.hpp>
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
  return ChangeLevel(input);
}

std::optional<std::unique_ptr<State>> LevelState::ChangeLevel(const Input& input)
{
  if (fadeState == Fade::OUT) return std::nullopt;

  if (input.k1Pressed) fadeState = Fade::OUT;
  if (fadeState == Fade::OUT_DONE)
    return std::make_unique<ExampleCollisionState>();

  if (input.k2Pressed) return std::make_unique<ExamplePathLevelState>();
  if (input.k3Pressed) return std::make_unique<ExampleWalkLevelState>();
  if (input.k4Pressed) return std::make_unique<ExampleScreenElementsLevelState>();

  return std::nullopt;
}