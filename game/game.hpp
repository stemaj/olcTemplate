#ifndef __GAME_HPP
#define __GAME_HPP

#include <game/src/state/state.hpp>
#include <memory>
#include <optional>

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
  void UpdateState();

private:
  std::unique_ptr<State> _currentState;
  std::optional<std::unique_ptr<State>> _nextState;
};

} // namespace stemaj

#endif //__GAME_HPP