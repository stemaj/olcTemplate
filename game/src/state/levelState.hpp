#ifndef __LEVELSTATE_HPP
#define __LEVELSTATE_HPP

#include <game/src/state/state.hpp>
#include <game/src/tools/pathfinding.hpp>
#include <game/src/tools/pathfollower.hpp>
#include <memory>

namespace stemaj {

class LevelRender;

class LevelState : public State
{
public:
  explicit LevelState();
  std::optional<std::unique_ptr<State>> Update(const Input& input, float fElapsedTime) override;
  Render* GetRender() override;
protected:
  std::optional<std::unique_ptr<State>> ChangeLevel(const Input& input);
private:
  virtual void LoadLevelData() {}
  virtual void SaveLevelData() {}
private:
  std::unique_ptr<LevelRender> _render;
};

} // namespace stemaj

#endif //__INTROSTATE_HPP