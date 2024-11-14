#ifndef __LOGOSTATE_HPP
#define __LOGOSTATE_HPP

#include <olcTemplate/game/animation.hpp>
#include <olcTemplate/game/input.hpp>
#include <olcTemplate/game/coordinates.hpp>
#include <olcTemplate/game/src/state/state.hpp>
#include <olcTemplate/game/src/tools/fader.hpp>

namespace olc {
  class Decal;
}

namespace stemaj {

class Render;
class LogoRender;

class LogoState : public State
{
public:
  explicit LogoState();
  std::optional<std::unique_ptr<State>> Update(const Input& input, float fElapsedTime) override;
  Render* GetRender() override;
  Fader _fader;

  Sheet _logoSheet;

private:
  std::optional<std::unique_ptr<State>> nextState();

  const float _logoTime = 8.0f;
  float _logoTimeCounter = 0.0f;
  bool _animationRewindedForStartup = false;

  std::unique_ptr<LogoRender> _render;
};

} // namespace stemaj

#endif //__LOGOSTATE_HPP