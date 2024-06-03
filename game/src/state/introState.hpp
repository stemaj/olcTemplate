#ifndef __INTROSTATE_HPP
#define __INTROSTATE_HPP

#include <chrono>
#include <olcTemplate/game/input.hpp>
#include <olcTemplate/game/src/state/state.hpp>

using timePoint = std::chrono::time_point<std::chrono::steady_clock,
  std::chrono::duration<long, std::ratio<1, 1000000000>>>;

namespace stemaj {

class IntroRender;

class IntroState : public State
{
public:

  enum class Parts
  {
    BLACK,
    OLCLOGO,
    RIEGEL,
    DADDY,
    VFC,
    GAME,
  };

  explicit IntroState();
  std::optional<std::unique_ptr<State>> Update(const Input& input, float fElapsedTime) override;
  Render* GetRender() override;

  float introEndDuration = 11.0f;
  float currentDuration = 0.0f;
  Parts _part = Parts::BLACK;

private:
  timePoint _introStartTime;

  std::unique_ptr<IntroRender> _render;
};

} // namespace stemaj

#endif //__INTROSTATE_HPP