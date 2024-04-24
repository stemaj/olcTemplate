#ifndef __EXAMPLEWALKLEVELSTATE_HPP
#define __EXAMPLEWALKLEVELSTATE_HPP

#include <game/src/state/levelState.hpp>
#define SOL_ALL_SAFETIES_ON 1
#include <sdk/sol2-3.3.0/sol.hpp>

namespace olc {
  class Decal;
}

namespace stemaj {

class ExampleWalkLevelRender;

class ExampleWalkLevelState : public LevelState
{
public:
  explicit ExampleWalkLevelState();
  virtual ~ExampleWalkLevelState();
  std::optional<std::unique_ptr<State>> Update(const Input& input, float fElapsedTime) override;
  Render* GetRender() override;

  PT<int> _drawPos;
  olc::Decal* _decal;
  PT<int> _sourceRectPos;
  PT<int> _sourceRectSize;
  PT<float> _scale;

private:
  void LoadLevelData() override;
  void SaveLevelData() override;
  sol::state _lua;
  std::unique_ptr<ExampleWalkLevelRender> _render;

  int _currentKind = 0;

  friend class ExampleWalkLevelRender;
};

} // namespace stemaj

#endif // __EXAMPLEWALKLEVELSTATE_HPP

