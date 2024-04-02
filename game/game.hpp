#ifndef __GAME_HPP
#define __GAME_HPP

#include <game/src/state/state.hpp>
#include <memory>

namespace olc {
  class PixelGameEngine;
}

namespace stemaj {

class Render;

class Game
{
public:
  Game();
  std::unique_ptr<Render> Update(Input input);
  void DoRender(olc::PixelGameEngine* pge, float fElapsedTime, std::unique_ptr<Render> render);
  void SetState(std::unique_ptr<State> newState);

private:
  std::unique_ptr<State> _currentState;
};

} // namespace stemaj

#endif //__GAME_HPP