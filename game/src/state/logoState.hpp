#ifndef __LOGOSTATE_HPP
#define __LOGOSTATE_HPP

#include <chrono>
#include <olcTemplate/game/input.hpp>
#include <olcTemplate/game/src/state/state.hpp>
#include <olcTemplate/game/coordinates.hpp>
#include <olcTemplate/game/src/tools/fader.hpp>
#include <olcTemplate/game/src/render/logoRender.hpp>
#define SOL_ALL_SAFETIES_ON 1
#include <olcTemplate/sdk/sol2-3.3.0/sol.hpp>


namespace olc {
  class Decal;
}

namespace stemaj {

class LogoState : public State
{
public:

  explicit LogoState();
  std::optional<std::unique_ptr<State>> Update(const Input& input, float fElapsedTime) override;
  Render* GetRender() override;
  Fader _fader;

  float introEndDuration = 18.0f;
  float currentDuration = 0.0f;

  PT<int> _bgDrawPos;
  olc::Decal* _bgDecal;
  PT<int> _bgSourceRectPos;
  PT<int> _bgSourceRectSize;
  PT<float> _bgScale;

private:

  sol::state _lua;

  std::chrono::high_resolution_clock::time_point _introStartTime = std::chrono::high_resolution_clock::now();

  std::unique_ptr<LogoRender> _render;
};

} // namespace stemaj

#endif //__LOGOSTATE_HPP