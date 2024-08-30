#include <olcTemplate/game/fonts.hpp>
#include <olcTemplate/game/src/tools/fader.hpp>
#include <olcTemplate/game/src/render/introRender.hpp>
#include <olcTemplate/game/src/state/introState.hpp>
#include <olcTemplate/game/src/engine/olcPGEX_QuickGUI.h>
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
  _fader = std::make_unique<Fader>(_lua["fade_time"].get_or(3.0f));
  _introTime = _lua["intro_time"].get_or(18.0f);
  _colors = _lua["colors"].get_or<std::vector<IntroColor>>({});
  _backgroundColorIndex = _lua["background_color"].get_or(0);
  
  sol::table textsTable = _lua["texts"].get_or(sol::table());
  for (size_t i = 1; i <= textsTable.size(); i++)
  {
    sol::table t = textsTable[i];
    auto p = t.get_or<std::array<float,2>>(2,{});
    _texts.push_back( {
      t.get_or<std::string>(1,""),
      CO.D({p[0],p[1]}),
      (FontSize)t.get_or(3,0),
      t.get_or(4,0.0f),
      t.get_or(5,0.0f),
      t.get_or(6,0)});
  }

  sol::table graphicsTable = _lua["graphics"];
  for (size_t i = 1; i <= graphicsTable.size(); i++)
  {
    sol::table t = graphicsTable[i];
    auto p = t.get<std::array<float,2>>(2);
    _graphics.push_back( {
      t.get<std::string>(1),
      CO.D({p[0],p[1]}),
      t.get<float>(3),
      t.get<float>(4),
      t.get<float>(5)});
  }

  _animations = _lua["animations"].get_or<std::vector<IntroAnimations>>({});

 
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
