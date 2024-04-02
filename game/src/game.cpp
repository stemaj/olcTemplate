#include <game/game.hpp>
#include <game/src/render/render.hpp>
#include <game/src/state/mainMenuState.hpp>
#include <memory>

using namespace stemaj;

Game::Game() : _currentState(std::make_unique<MainMenuState>())
{
}

void Game::Update(const Input& input)
{
  _currentState->Update(input);
}

void Game::Render(olc::PixelGameEngine* pge, float fElapsedTime)
{
  _currentState->GetRender()->DoRender(pge,fElapsedTime,_currentState.get());
}
