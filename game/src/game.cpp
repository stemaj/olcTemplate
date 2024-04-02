#include <game/game.hpp>
#include <game/src/render/render.hpp>
#include <memory>

using namespace stemaj;

Game::Game()
{

}

std::unique_ptr<Render> Game::Update(Input input)
{
  return nullptr;
}

void Game::DoRender(olc::PixelGameEngine* pge, float fElapsedTime, std::unique_ptr<Render> render)
{
  
}

void Game::SetState(std::unique_ptr<State> newState)
{

}
