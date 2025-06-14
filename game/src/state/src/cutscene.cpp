#include <olcTemplate/game/src/render/renderCutscene.hpp>
#include <olcTemplate/game/src/state/cutscene.hpp>
#include <olcTemplate/game/fonts.hpp>
#include <olcTemplate/game/src/tools/fader.hpp>
#include <game/cheetahLevel.hpp>
#include <olcTemplate/game/src/state/mainMenuState.hpp>
#include <optional>
#include <olcTemplate/sdk/imgui-1.90.4/imgui.h>
#include <olcTemplate/game/sound.hpp>
#include <olcTemplate/game/loadsave.hpp>

using namespace stemaj;

Cutscene::Cutscene(const std::string& name, const std::string& tryAgainLevelName) 
: _name(name), _tryAgainLevelName(tryAgainLevelName), _render(std::make_unique<RenderCutscene>())
{
  //SO.StartMusic("./olcTemplate/assets/wav/groovy-energy-sports-80-bpm-short-12275.mp3", 0.5f);

  LS.Init("./scripts/" + name + ".lua", false);
  _font = LS.String("font", "dogica");
  _fader = std::make_unique<Fader>(LS.Float("fade_time", 3.0f));
  _cutsceneTime = LS.Float("cutscene_time", 18.0f);
  _colors = LS.Colors();
  _backgroundColorIndex = LS.Int("background_color", 0);
  _texts = LS.IntroTexts();
  _graphics = LS.IntroGraphics();
}

Render* Cutscene::GetRender()
{
  return _render.get();
}

std::optional<std::unique_ptr<State>> Cutscene::Update(const Input& input, float fElapsedTime)
{
  if (!_animationRewindedForStartup)
  {
		fElapsedTime = 0.0f;
    _fader->StartFadeIn();
		_animationRewindedForStartup = true;
  }

  _currentTime += fElapsedTime;
  auto timeInPercent = _currentTime / _cutsceneTime;

  _activeTextIndicies.clear();
  for (int i = 0; i < _texts.size(); i++)
  {
    if (timeInPercent > _texts[i].startTime && timeInPercent < _texts[i].endTime)
    {
      _activeTextIndicies.push_back(i);
    }
  }
  _activeGraphicIndicies.clear();
  for (int i = 0; i < _graphics.size(); i++)
  {
    if (timeInPercent > _graphics[i].startTime && timeInPercent < _graphics[i].endTime)
    {
      _activeGraphicIndicies.push_back(i);
    }
  }

  if (input.spacePressed || input.leftMouseClicked)
  {
    if (_name == "cutscene_end_good" || _name == "cutscene_end_bad")
    {
      return std::make_unique<MainMenuState>();
    }
    else if (_name == "cutscene_lose")
    {
      return std::make_unique<CheetahLevel>(_tryAgainLevelName);
    }
    else // next level 
    {
      return std::make_unique<CheetahLevel>(_name.replace(0,9,""));
    }
  }

  if (_currentTime < _cutsceneTime)
  {
    if (_fader->IsFading())
    {
      // fade in
      _fader->Update(fElapsedTime);
    }
  }
  else
  {
    if (_fader->IsTurning())
    {
      if (_name == "cutscene_end_good" || _name == "cutscene_end_bad")
      {
        return std::make_unique<MainMenuState>();
      }
      else if (_name == "cutscene_lose")
      {
        return std::make_unique<CheetahLevel>(_tryAgainLevelName);
      }
      else // next level 
      {
        return std::make_unique<CheetahLevel>(_name.replace(0,9,""));
      }
    }
    else if (!_fader->IsFading())
    {
      //SO.StopMusic(0.9f);
      _fader->StartFadeOut();
    }
    else
    {
      // fade out
      _fader->Update(fElapsedTime);
    }
  }

  return std::nullopt;
}
