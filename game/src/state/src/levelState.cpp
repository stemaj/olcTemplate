#include <olcTemplate/game/src/state/levelState.hpp>
#include <olcTemplate/game/src/render/levelRender.hpp>
// #include <game/src/state/exampleCollisionState.hpp>
// #include <game/src/state/examplePathLevelState.hpp>
// #include <game/src/state/exampleWalkLevelState.hpp>
// #include <game/src/state/exampleScreenElementsLevelState.hpp>
#include <optional>
#include <olcTemplate/sdk/imgui-1.90.4/imgui.h>

using namespace stemaj;

LevelState::LevelState() : _fader(0.3f), _render(std::make_unique<LevelRender>())
{
  _fader.StartFadeIn();
}

Render* LevelState::GetRender()
{
  return _render.get();
}

std::optional<std::unique_ptr<State>> LevelState::Update(const Input& input, float fElapsedTime)
{
 return ChangeLevel(input, fElapsedTime);
}

std::optional<std::unique_ptr<State>> LevelState::ChangeLevel(const Input& input, float fElapsedTime)
{
  if (!_fader.IsFading())
  {
    // if (input.k1Pressed)
    // {
    //   _fader.StartFadeOut();
    //   _levelToChange = std::make_unique<ExampleCollisionState>();
    // }
    // if (input.k2Pressed)
    // {
    //   _fader.StartFadeOut();
    //   _levelToChange = std::make_unique<ExamplePathLevelState>();
    // }
    // if (input.k3Pressed)
    // {
    //   _fader.StartFadeOut();
    //   _levelToChange = std::make_unique<ExampleWalkLevelState>();
    // }
    // if (input.k4Pressed)
    // {
    //   _fader.StartFadeOut();
    //   _levelToChange = std::make_unique<ExampleScreenElementsLevelState>();
    // }
  }
  else
  {
    _fader.Update(fElapsedTime);
    if (!_fader.IsFading())
    {
      return std::move(_levelToChange);
    }
  }

  return std::nullopt;  
}