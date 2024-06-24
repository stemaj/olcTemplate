#include <chrono>
#include <olcTemplate/game/src/state/introState.hpp>
#include <olcTemplate/game/src/state/mainMenuState.hpp>
#include <olcTemplate/game/animation.hpp>
#include <optional>
#include <olcTemplate/sdk/imgui-1.90.4/imgui.h>

using namespace stemaj;

olc::utils::Animate2D::AnimationState introBackgroundAnimationState;
olc::utils::Animate2D::AnimationState introCharacterAnimationState;

IntroState::IntroState() : _fader(3.0f), _render(std::make_unique<IntroRender>())
{
  _fader.StartFadeIn();

  _lua.open_libraries(sol::lib::base, sol::lib::io, sol::lib::math, sol::lib::table);

	try
	{
		_lua.safe_script_file("scripts/intro.lua");
	}
	catch (const sol::error& e)
	{
		std::cout << std::string(e.what()) << std::endl;
	}

  _font = _lua["font"].get_or<std::string>("dogica");
  _nameOfTheGame = _lua["name_of_the_game"].get_or<std::string>("NAME OF THE GAME");
  _copyright = _lua["copyright"].get_or<std::string>("(c) riegel games");

  std::vector<float> cppArray = _lua["header_color"].get_or<std::vector<float>>({});
  for (int i = 0; i < cppArray.size(); i++)
  {
    _headerColor[i] = cppArray[i];
  }

  auto pt = _lua["olc_logo_pos"].get_or<std::array<float,2>>({});
  _olcLogoPos = PT<float>{pt[0],pt[1]};
  pt = _lua["riegel_pos"].get_or<std::array<float,2>>({});
  _riegelPos = PT<float>{pt[0],pt[1]};
  pt = _lua["daddy_pos"].get_or<std::array<float,2>>({});
  _daddyPos = PT<float>{pt[0],pt[1]};
  pt = _lua["vfc_pos"].get_or<std::array<float,2>>({});
  _vfcPos = PT<float>{pt[0],pt[1]};
  pt = _lua["name_of_the_game_pos"].get_or<std::array<float,2>>({});
  _nameOfTheGamePos = PT<float>{pt[0],pt[1]};
  pt = _lua["copyright_pos"].get_or<std::array<float,2>>({});
  _copyrightPos = PT<float>{pt[0],pt[1]};
}

Render* IntroState::GetRender()
{
  return _render.get();
}

std::optional<std::unique_ptr<State>> IntroState::Update(const Input& input, float fElapsedTime)
{
#if defined(STEMAJ_DEBUG)
  // ImGui::Begin("Intro Debug");
  // ImGui::Text("Mouse Position: (%d, %d)", input.mouseX, input.mouseY);
  // ImGui::Text("Duration: (%f)", currentDuration);
  // ImGui::Text("Part: (%d)", _part);
  // ImGui::End();
#endif

  auto bgAnim = AN.GetAnimation("pretty_pretty_bg_25pc");
  bgAnim.animation.ChangeState(introBackgroundAnimationState, IDLE);
  const auto& bgFrame = bgAnim.animation.GetFrame(introBackgroundAnimationState);
  bgAnim.animation.UpdateState(introBackgroundAnimationState, fElapsedTime);

  _bgDrawPos = PT<int>{ 0,0 };
  _bgDecal = bgFrame.GetSourceImage()->Decal();
  _bgSourceRectPos = {bgFrame.GetSourceRect().pos.x,bgFrame.GetSourceRect().pos.y};
  _bgSourceRectSize = {bgFrame.GetSourceRect().size.x,bgFrame.GetSourceRect().size.y};
  float scale =  CO.W / (float)_bgSourceRectSize.x;
  _bgScale = PT<float>{scale,scale};

  auto chAnim = AN.GetAnimation("pretty_pretty_ch_25pc");
  chAnim.animation.ChangeState(introCharacterAnimationState, IDLE);
  const auto& chFrame = chAnim.animation.GetFrame(introCharacterAnimationState);
  chAnim.animation.UpdateState(introCharacterAnimationState, fElapsedTime);

  _chDrawPos = PT<int>{ CO.W * 3 / 5,0 };
  _chDecal = chFrame.GetSourceImage()->Decal();
  _chSourceRectPos = {chFrame.GetSourceRect().pos.x,chFrame.GetSourceRect().pos.y};
  _chSourceRectSize = {chFrame.GetSourceRect().size.x,chFrame.GetSourceRect().size.y};
  scale =  CO.H / (float)_bgSourceRectSize.y;
  _chScale = PT<float>{scale,scale};

  auto now = std::chrono::high_resolution_clock::now();
  currentDuration = std::chrono::duration_cast<std::chrono::milliseconds>(now - _introStartTime).count() / 1000.0f;
  if (currentDuration < introEndDuration)
  {
    if (currentDuration > (introEndDuration * 0.19f) && currentDuration < (introEndDuration * 0.31f))
    {
      _part = Parts::OLCLOGO;
    }
    else if (currentDuration > (introEndDuration * 0.33f) && currentDuration < (introEndDuration * 0.45f))
    {
      _part = Parts::RIEGEL;
    }
    else if (currentDuration > (introEndDuration * 0.47f) && currentDuration < (introEndDuration * 0.59f))
    {
      _part = Parts::DADDY;
    }
    else if (currentDuration > (introEndDuration * 0.61f) && currentDuration < (introEndDuration * 0.73f))
    {
      _part = Parts::VFC;
    }
    else if (currentDuration > (introEndDuration * 0.75f))
    {
      _part = Parts::GAME;
    }
    else
    {
      _part = Parts::BLACK;
    }

    if (input.spacePressed)
    {
      return std::make_unique<MainMenuState>();
    }
  }
  else if (!_fader.IsFading())
  {
    _fader.StartFadeOut();
  }

  _fader.Update(fElapsedTime);
  if (_fader.IsTurning())
  {
    return std::make_unique<MainMenuState>();
  }
  return std::nullopt;
}
