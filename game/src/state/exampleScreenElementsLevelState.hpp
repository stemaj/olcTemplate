#ifndef __EXAMPLESCREENELEMENTSLEVELSTATE_HPP
#define __EXAMPLESCREENELEMENTSLEVELSTATE_HPP

#include <game/src/state/levelState.hpp>
#define SOL_ALL_SAFETIES_ON 1
#include <sdk/sol2-3.3.0/sol.hpp>

namespace stemaj {

class ExampleScreenElementsLevelRender;

class ExampleScreenElementsLevelState : public LevelState
{
public:
  explicit ExampleScreenElementsLevelState();
  virtual ~ExampleScreenElementsLevelState();
  std::optional<std::unique_ptr<State>> Update(const Input& input, float fElapsedTime) override;
  Render* GetRender() override;

private:
  void LoadLevelData() override;
  void SaveLevelData() override;
  sol::state _lua;
  std::unique_ptr<ExampleScreenElementsLevelRender> _render;

  friend class ExampleScreenElementsLevelRender;
};

} // namespace stemaj

#endif // __EXAMPLESCREENELEMENTSLEVELSTATE_HPP

