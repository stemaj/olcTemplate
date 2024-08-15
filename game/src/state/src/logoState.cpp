#include "olcTemplate/game/src/state/introState.hpp"
#include <olcTemplate/game/src/state/logoState.hpp>
#include <olcTemplate/game/src/state/mainMenuState.hpp>
#include <olcTemplate/game/animation.hpp>
#include <optional>
#include <olcTemplate/sdk/imgui-1.90.4/imgui.h>
#include <olcTemplate/game/sound.hpp>

using namespace stemaj;

LogoState::LogoState() : _fader(0.9f), _render(std::make_unique<LogoRender>())
{
	SO.Play("./olcTemplate/assets/wav/breaking-news-177297.mp3");

  // no fade in

  _lua.open_libraries(sol::lib::base, sol::lib::io, sol::lib::math, sol::lib::table);
	try
	{
		_lua.safe_script_file("scripts/settings.lua");
	}
	catch (const sol::error& e)
	{
		std::cout << std::string(e.what()) << std::endl;
	}
}

Render* LogoState::GetRender()
{
  return _render.get();
}

std::optional<std::unique_ptr<State>> LogoState::nextState()
{
  bool showIntro = _lua["show_intro"].get_or(false);
  if (showIntro)
  {
    return std::make_unique<IntroState>();                
  }
  return std::make_unique<MainMenuState>();
}

std::optional<std::unique_ptr<State>> LogoState::Update(const Input& input, float fElapsedTime)
{
  if (input.spacePressed || input.leftMouseClicked)
  {
    return nextState();
  }
  if (!_animationRewindedForStartup)
  {
		fElapsedTime = 0.0f;
		_animationRewindedForStartup = true;
  }

  auto a = AN.GetAnimation("Sing_With_Me");
  const auto& frame = a.animation.GetFrame(_logoSheet.animationState);
  a.animation.UpdateState(_logoSheet.animationState, fElapsedTime);

  _logoSheet.decal = frame.GetSourceImage()->Decal();
  _logoSheet.sourceRectPos = {frame.GetSourceRect().pos.x,frame.GetSourceRect().pos.y};
  _logoSheet.sourceRectSize = {frame.GetSourceRect().size.x,frame.GetSourceRect().size.y};
  float scale =  std::min(CO.H / (float)_logoSheet.sourceRectSize.y,
                          CO.W / (float)_logoSheet.sourceRectSize.x);
  _logoSheet.scale = PT<float>{scale,scale};

  PT<int> mid = { CO.W / 2, CO.H / 2 };
  _logoSheet.pos = {mid.x - (_logoSheet.sourceRectSize.x * _logoSheet.scale.x) / 2,
                    mid.y - (_logoSheet.sourceRectSize.y * _logoSheet.scale.y) / 2};


  _logoTimeCounter += fElapsedTime;
  if (_logoTimeCounter > _logoTime)
  {
    if (!_fader.IsFading())
    {
			SO.Stop(0.9f);
      _fader.StartFadeOut();
    }
    _fader.Update(fElapsedTime);
    if (_fader.IsTurning())
    {
      return nextState();
    }
  }

  return std::nullopt;
}
