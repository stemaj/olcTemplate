#ifndef __LEVELSTATE_HPP
#define __LEVELSTATE_HPP

#include <olcTemplate/game/src/tools/fader.hpp>
#include <olcTemplate/game/src/state/state.hpp>
#include <olcTemplate/game/src/render/levelRender.hpp>
#include <memory>

namespace stemaj {

class LevelRender;

class LevelState : public State
{
public:
  explicit LevelState();
  std::optional<std::unique_ptr<State>> Update(const Input& input,
    float fElapsedTime) override;
  Render* GetRender() override;
  Fader _fader;

protected:
  std::optional<std::unique_ptr<State>> ChangeLevel(
    const Input& input, float fElapsedTime);
private:
  std::optional<std::unique_ptr<State>> _levelToChange;
  virtual void LoadLevelData() {}
  virtual void SaveLevelData() {}
private:
  std::unique_ptr<LevelRender> _render;
};

} // namespace stemaj

#endif //__INTROSTATE_HPP
