#include "olcTemplate/game/sound.hpp"
#include <chrono>
#include <olcTemplate/game/src/state/logoState.hpp>
#include <olcTemplate/game/src/state/mainMenuState.hpp>
#include <olcTemplate/game/animation.hpp>
#include <optional>
#include <olcTemplate/sdk/imgui-1.90.4/imgui.h>

using namespace stemaj;

olc::utils::Animate2D::AnimationState logoBackgroundAnimationState;

LogoState::LogoState() : _fader(0.01f), _render(std::make_unique<LogoRender>())
{
  _fader.StartFadeIn();
}

Render* LogoState::GetRender()
{
  return _render.get();
}

std::optional<std::unique_ptr<State>> LogoState::Update(const Input& input, float fElapsedTime)
{
  if (input.spacePressed || input.leftMouseClicked)
  {
    return std::make_unique<MainMenuState>();
  }

  std::cout << "State\n";
  auto bgAnim = AN.GetAnimation("Sing_With_Me");

  if (!one)
  {

  bgAnim.animation.ChangeState(logoBackgroundAnimationState, IDLE);
    logoBackgroundAnimationState.fTime = 0.0f;
    logoBackgroundAnimationState.nIndex = 0;
  
  // bgAnim.animation.ChangeState(logoBackgroundAnimationState, MOVERIGHT);
  // bgAnim.animation.UpdateState(logoBackgroundAnimationState, fElapsedTime);
  one = true;
  }
  const auto& bgFrame = bgAnim.animation.GetFrame(logoBackgroundAnimationState);
  bgAnim.animation.UpdateState(logoBackgroundAnimationState, fElapsedTime);

  _bgDecal = bgFrame.GetSourceImage()->Decal();
  _bgSourceRectPos = {bgFrame.GetSourceRect().pos.x,bgFrame.GetSourceRect().pos.y};
  _bgSourceRectSize = {bgFrame.GetSourceRect().size.x,bgFrame.GetSourceRect().size.y};
  float scale =  std::min(CO.H / (float)_bgSourceRectSize.y, CO.W / (float)_bgSourceRectSize.x);
  _bgScale = PT<float>{scale,scale};
  PT<int> mid = { CO.W / 2, CO.H / 2 };
  _bgDrawPos = PT<int>{ mid.x - (_bgSourceRectSize.x * _bgScale.x) / 2,mid.y - (_bgSourceRectSize.y * _bgScale.y) / 2 };


  // else if (!_fader.IsFading())
  // {
  //   _fader.StartFadeOut();
  // }

  // _fader.Update(fElapsedTime);
  // if (_fader.IsTurning())
  // {
  //   return std::make_unique<MainMenuState>();
  // }
  return std::nullopt;
}
