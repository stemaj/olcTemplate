#include <olcTemplate/game/src/state/mainMenuState.hpp>
#include <olcTemplate/game/src/state/levelState.hpp>
#include <memory>
#include <optional>
#include <olcTemplate/sdk/imgui-1.90.4/imgui.h>

using namespace stemaj;

LevelState::LevelState() : _fader(0.3f), _render(std::make_unique<LevelRender>())
{
  _fader.StartFadeIn();
  _camera = olc::utils::Camera2D({(float)CO.W, (float)CO.H});
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
   if (input.backSpacePressed)
   {
    _fader.StartFadeOut();
    _levelToChange = std::make_unique<MainMenuState>();
   }
   _fader.Update(fElapsedTime);
   return _fader.IsTurning() ? std::move(_levelToChange) : std::nullopt;
}
