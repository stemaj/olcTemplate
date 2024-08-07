#ifndef __LOADING_HPP
#define __LOADING_HPP

#include <olcTemplate/game/src/state/state.hpp>
#include <olcTemplate/game/src/tools/fader.hpp>
#include <olcTemplate/game/src/render/loadingRender.hpp>

namespace olc {
  class Decal;
}

namespace stemaj {

class Loading : public State
{
public:

  explicit Loading();
  std::optional<std::unique_ptr<State>> Update(const Input& input, float fElapsedTime) override;
  Render* GetRender() override;

  float endTime = 5.0f;
  float timer = 0.0f;
  bool ended = false;
  bool loadingStarted = false;
private:
  std::unique_ptr<LoadingRender> _render;
};

} // namespace stemaj

#endif //__LOADING_HPP