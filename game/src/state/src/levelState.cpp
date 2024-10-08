#include <olcTemplate/game/src/state/levelState.hpp>
#include <olcTemplate/game/src/render/levelRender.hpp>
#include <olcTemplate/game/src/engine/olcPGEX_QuickGUI.h>
#include <olcTemplate/game/src/state/mainMenuState.hpp>
#include <olcTemplate/game/src/render/mainMenuRender.hpp>
#include <olcTemplate/game/sound.hpp>
#include <olcTemplate/sdk/imgui-1.90.4/imgui.h>
#include <memory>
#include <optional>

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
   if (input.escapePressed)
   {
    stopAllEffects();
	  stopMusic();
    _fader.StartFadeOut();
    _levelToChange = std::make_unique<MainMenuState>();
   }
   _fader.Update(fElapsedTime);
   return _fader.IsTurning() ? std::move(_levelToChange) : std::nullopt;
}

void LevelState::playMusic(const std::string& filePath, const float fadeTime)
{
  SO.StartMusic(filePath, 0.2f, fadeTime);
}

void LevelState::stopMusic(const float fadeTime)
{
  SO.StopAllEffects();
  SO.StopMusic(fadeTime);
}

void LevelState::playEffect(const std::string& filePath)
{
  SO.StartEffect(filePath, 1.0f);
}

void LevelState::stopAllEffects()
{
  SO.StopAllEffects();
}