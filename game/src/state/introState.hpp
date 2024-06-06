#ifndef __INTROSTATE_HPP
#define __INTROSTATE_HPP

#include <chrono>
#include <olcTemplate/game/input.hpp>
#include <olcTemplate/game/src/state/state.hpp>
#include <olcTemplate/game/coordinates.hpp>
#include <olcTemplate/game/src/tools/fader.hpp>

using timePoint = std::chrono::time_point<std::chrono::steady_clock,
  std::chrono::duration<long, std::ratio<1, 1000000000>>>;

namespace olc {
  class Decal;
}

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
  Fader _fader;

  float introEndDuration = 18.0f;
  float currentDuration = 0.0f;
  Parts _part = Parts::BLACK;

  PT<int> _bgDrawPos;
  olc::Decal* _bgDecal;
  PT<int> _bgSourceRectPos;
  PT<int> _bgSourceRectSize;
  PT<float> _bgScale;

  PT<int> _chDrawPos;
  olc::Decal* _chDecal;
  PT<int> _chSourceRectPos;
  PT<int> _chSourceRectSize;
  PT<float> _chScale;

private:
  timePoint _introStartTime;

  std::unique_ptr<IntroRender> _render;
};

} // namespace stemaj

#endif //__INTROSTATE_HPP