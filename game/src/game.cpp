#include <game/src/state/introState.hpp>
#include <game/game.hpp>
#include <game/src/render/render.hpp>
#include <game/src/render/levelRender.hpp>
#include <game/src/state/levelState.hpp>

using namespace stemaj;

Game::Game() : _currentState(std::make_unique<LevelState>())
{
}

void Game::Update(const Input& input, float fElapsedTime)
{
  _nextState = _currentState->Update(input, fElapsedTime);
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
