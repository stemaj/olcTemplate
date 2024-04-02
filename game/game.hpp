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
  void Update(const Input& input);
  void Render(olc::PixelGameEngine* pge, float fElapsedTime);

private:
  std::unique_ptr<State> _currentState;
};

} // namespace stemaj

#endif //__GAME_HPP