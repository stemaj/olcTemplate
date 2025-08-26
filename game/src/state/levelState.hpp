#ifndef __LEVELSTATE_HPP
#define __LEVELSTATE_HPP

#include <olcTemplate/game/src/tools/fader.hpp>
#include <olcTemplate/game/src/state/state.hpp>
#include <olcTemplate/game/src/engine/olcUTIL_Camera2D.h>
#include <memory>

namespace stemaj {

class Render;
class LevelRender;

class LevelState : public State
{
public:
  explicit LevelState(std::unique_ptr<State> onNext = nullptr,
    std::unique_ptr<State> onAgain = nullptr);
  std::optional<std::unique_ptr<State>> Update(const Input& input,
    float fElapsedTime) override;
  Render* GetRender() override;
  void setNext(std::unique_ptr<State> onNext) override { _onNext = std::move(onNext); }
  void setAgain(std::unique_ptr<State> onAgain) override { _onAgain = std::move(onAgain); }
  Fader _fader;

protected:
  std::optional<std::unique_ptr<State>> RequestForMainMenu(
    bool escapeTriggered, float fElapsedTime);

  olc::utils::Camera2D _camera;
  bool _cameraConfigured = false;

private:
  virtual void LoadLevelData() {}
  virtual void SaveLevelData() {}
private:
  std::unique_ptr<LevelRender> _render;
};

} // namespace stemaj

#endif //__INTROSTATE_HPP
