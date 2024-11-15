#include "olcTemplate/game/loadsave.hpp"
#include <olcTemplate/game/fonts.hpp>
#include <olcTemplate/game/src/tools/fader.hpp>
#include <olcTemplate/game/src/render/introRender.hpp>
#include <olcTemplate/game/src/state/introState.hpp>
#include <olcTemplate/game/src/render/mainMenuRender.hpp>
#include <olcTemplate/game/src/state/mainMenuState.hpp>
#include <olcTemplate/game/animation.hpp>
#include <optional>
#include <olcTemplate/sdk/imgui-1.90.4/imgui.h>
#include <olcTemplate/game/sound.hpp>

using namespace stemaj;

olc::utils::Animate2D::AnimationState introBackgroundAnimationState;
olc::utils::Animate2D::AnimationState introCharacterAnimationState;

IntroState::IntroState() : _render(std::make_unique<IntroRender>())
{
  SO.StartMusic("./olcTemplate/assets/wav/groovy-energy-sports-80-bpm-short-12275.mp3", 0.5f);

  LS.Init("scripts/intro.lua", false);
  _font = LS.String("font", "dogica");
  _fader = std::make_unique<Fader>(LS.Float("fade_time", 3.0f));
  _introTime = LS.Float("intro_time", 18.0f);
  _colors = LS.Colors();
  _backgroundColorIndex = LS.Int("background_color");
  _texts = LS.IntroTexts();
  _graphics = LS.IntroGraphics();
  _animations = LS.VString("animations");
 
  for (const auto& a : _animations)
  {
    Sheet s;
    s.asset = AN.GetAnimation(a);
    s.asset.animation.ChangeState(s.animationState, IDLE);
    _sheets.push_back(s);
  }
}

Render* IntroState::GetRender()
{
  return _render.get();
}

std::optional<std::unique_ptr<State>> IntroState::Update(const Input& input, float fElapsedTime)
{
  if (!_animationRewindedForStartup)
  {
		fElapsedTime = 0.0f;
    _fader->StartFadeIn();
		_animationRewindedForStartup = true;
  }

  _currentTime += fElapsedTime;
  auto timeInPercent = _currentTime / _introTime;

  for (auto& s : _sheets)
  {
    s.asset.animation.UpdateState(s.animationState, fElapsedTime);

    const auto& frame = s.asset.animation.GetFrame(s.animationState);
    s.decal = frame.GetSourceImage()->Decal();
    s.sourceRectPos = { frame.GetSourceRect().pos.x, frame.GetSourceRect().pos.y };
    s.sourceRectSize = { frame.GetSourceRect().size.x, frame.GetSourceRect().size.y };
    float scale =  std::max(CO.W / (float)s.sourceRectSize.x, CO.H / (float)s.sourceRectSize.y);
    s.scale = {scale,scale};
  }

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
    return std::make_unique<MainMenuState>();
  }

  if (_currentTime < _introTime)
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
      return std::make_unique<MainMenuState>();
    }
    else if (!_fader->IsFading())
    {
      SO.StopMusic(0.9f);
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
