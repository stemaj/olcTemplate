#ifndef __INTROSTATE_HPP
#define __INTROSTATE_HPP

#include <chrono>
#include <memory>
#include <game/input.hpp>
#include <game/src/state/state.hpp>
#include <game/src/render/introRender.hpp>

using timePoint = std::chrono::time_point<std::chrono::steady_clock,
  std::chrono::duration<long, std::ratio<1, 1000000000>>>;

namespace stemaj {

class IntroState : public State
{
public:
  explicit IntroState();
  std::optional<std::unique_ptr<State>> Update(const Input& input) override;
  Render* GetRender() override;

  float introEndDuration = 1.0f;
  float currentDuration = 0.0f;

private:
  timePoint _introStartTime;

  std::unique_ptr<IntroRender> _render;
};

} // namespace stemaj

#endif //__INTROSTATE_HPP