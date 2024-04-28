#ifndef __EXAMPLESCREENELEMENTSLEVELSTATE_HPP
#define __EXAMPLESCREENELEMENTSLEVELSTATE_HPP

#include <game/src/state/levelState.hpp>
#include <vector>
#define SOL_ALL_SAFETIES_ON 1
#include <sdk/sol2-3.3.0/sol.hpp>

namespace stemaj {

class ExampleScreenElementsLevelRender;

class ExampleScreenElementsLevelState : public LevelState
{
public:

  struct Textbox
  {
    std::string _text = "stemaj Template";
    PT<int> _boxUpperLeft = {0,0 };
    PT<int> _frameboxSize = {0,0 };
    PT<int> _frameboxUpperLeft = {0,0 };
		
		int location = 1; // offset upper left
		
		std::array<PT<int>, 4> _points;
  };

  explicit ExampleScreenElementsLevelState();
  virtual ~ExampleScreenElementsLevelState();
  std::optional<std::unique_ptr<State>> Update(const Input& input, float fElapsedTime) override;
  Render* GetRender() override;

  PT<int> _mousePos = {0,0 };
  std::vector<Textbox> _textboxes;

private:
  void LoadLevelData() override;
  void SaveLevelData() override;
  sol::state _lua;
  std::unique_ptr<ExampleScreenElementsLevelRender> _render;

  friend class ExampleScreenElementsLevelRender;
};

} // namespace stemaj

#endif // __EXAMPLESCREENELEMENTSLEVELSTATE_HPP

