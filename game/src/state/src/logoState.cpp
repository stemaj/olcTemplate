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
  auto bgAnim = AN.GetAnimation("Sing_With_Me");
  bgAnim.animation.ChangeState(logoBackgroundAnimationState, IDLE);
  const auto& bgFrame = bgAnim.animation.GetFrame(logoBackgroundAnimationState);
  bgAnim.animation.UpdateState(logoBackgroundAnimationState, fElapsedTime);

  _bgDrawPos = PT<int>{ 0,0 };
  _bgDecal = bgFrame.GetSourceImage()->Decal();
  _bgSourceRectPos = {bgFrame.GetSourceRect().pos.x,bgFrame.GetSourceRect().pos.y};
  _bgSourceRectSize = {bgFrame.GetSourceRect().size.x,bgFrame.GetSourceRect().size.y};
  float scale =  CO.H / (float)_bgSourceRectSize.x;
  _bgScale = PT<float>{scale,scale};

  if (input.spacePressed || input.leftMouseClicked)
  {
    return std::make_unique<MainMenuState>();
  }
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
