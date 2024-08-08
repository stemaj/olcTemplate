#include <olcTemplate/game/src/state/loading.hpp>
#include <olcTemplate/game/src/state/logoState.hpp>
#include <olcTemplate/game/src/state/mainMenuState.hpp>
#include <olcTemplate/game/src/state/introState.hpp>
#include <olcTemplate/game/game.hpp>
#include <olcTemplate/game/src/render/render.hpp>

using namespace stemaj;

Game::Game()
{
  sol::state lua;
  lua.open_libraries(sol::lib::base, sol::lib::io, sol::lib::math, sol::lib::table);
	try
	{
		lua.safe_script_file("scripts/settings.lua");
	}
	catch (const sol::error& e)
	{
		std::cout << std::string(e.what()) << std::endl;
	}

  _currentState = std::make_unique<Loading>();
}

void Game::Update(const Input& input, float fElapsedTime)
{
  _nextState = _currentState->Update(input, fElapsedTime);
}

void Game::Render(olc::PixelGameEngine* pge, float fElapsedTime)
{
  if (_currentState->GetRender() != nullptr)
  {
    _currentState->GetRender()->DoRender(pge,fElapsedTime,_currentState.get());
    _currentState->GetRender()->Fade(pge,_currentState.get());
  }
}

void Game::UpdateState()
{
  if (_nextState.has_value())
  {
    _currentState = std::move(_nextState.value());
  }
}
