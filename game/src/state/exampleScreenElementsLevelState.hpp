#ifndef __EXAMPLESCREENELEMENTSLEVELSTATE_HPP
#define __EXAMPLESCREENELEMENTSLEVELSTATE_HPP

#include <game/src/state/levelState.hpp>
#include <vector>
#define SOL_ALL_SAFETIES_ON 1
#include <sdk/sol2-3.3.0/sol.hpp>

#include <game/geometryWrapper.hpp>

namespace stemaj {

class ExampleScreenElementsLevelRender;
class TextBox;

class ExampleScreenElementsLevelState : public LevelState
{
public:

  explicit ExampleScreenElementsLevelState();
  virtual ~ExampleScreenElementsLevelState();
  std::optional<std::unique_ptr<State>> Update(const Input& input, float fElapsedTime) override;
  Render* GetRender() override;

  std::vector<TextBox> _textboxes;
  PT<int> _mousePos;
  
  Circle _circle = Circle({100,100}, 25);
  Rect _rect = Rect({150,150}, {20,30});
  struct Color
  {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t alpha;
    friend std::ostream& operator<<(std::ostream& os, const Color& obj) {
      os << "{ r: " << obj.r << ", g: " << obj.g << ", b: " << obj.b << ", alpha: " << obj.alpha << " }\n";
      return os;
    }

  };
  Color _color;

private:
  void LoadLevelData() override;
  void SaveLevelData() override;
  sol::state _lua;
  std::unique_ptr<ExampleScreenElementsLevelRender> _render;

  friend class ExampleScreenElementsLevelRender;
};

} // namespace stemaj

#endif // __EXAMPLESCREENELEMENTSLEVELSTATE_HPP

