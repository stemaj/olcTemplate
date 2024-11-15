#include <olcTemplate/game/game.hpp>
#include <olcTemplate/game/src/render/loadingRender.hpp>
#include <olcTemplate/game/src/state/loading.hpp>

using namespace stemaj;

Game::Game()
{
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
