#include <game/src/state/introState.hpp>
#include <game/game.hpp>
#include <game/src/render/render.hpp>

using namespace stemaj;

Game::Game() : _currentState(std::make_unique<IntroState>())
{
}

void Game::Update(const Input& input)
{
  _nextState = _currentState->Update(input);
}

void Game::Render(olc::PixelGameEngine* pge, float fElapsedTime)
{
  _currentState->GetRender()->DoRender(pge,fElapsedTime,_currentState.get());
}

void Game::UpdateState()
{
  if (_nextState.has_value())
  {
    _currentState = std::move(_nextState.value());
  }
}