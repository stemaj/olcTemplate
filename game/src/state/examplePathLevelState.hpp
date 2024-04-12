#ifndef __EXAMPLEPATHLEVELSTATE_HPP
#define __EXAMPLEPATHLEVELSTATE_HPP

#include <game/coordinates.hpp>
#include <game/src/render/examplePathLevelRender.hpp>
#include <game/src/state/levelState.hpp>
#define SOL_ALL_SAFETIES_ON 1
#include <sdk/sol2-3.3.0/sol.hpp>

namespace stemaj {

//class ExamplePathLevelRender;

class ExamplePathLevelState : public LevelState
{
public:
  explicit ExamplePathLevelState();
  virtual ~ExamplePathLevelState();
  std::optional<std::unique_ptr<State>> Update(const Input& input) override;
  Render* GetRender() override;
private:
  PT<int> _grid;
  PT<int> _start;

  std::vector<PT<int>> _displayGrid;
  PT<int> _displayStart;
  PT<int> _displayEnd;
  std::vector<PT<int>> _displayPath;

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
  Color _colorBackground;
  Color _colorObject;
  Color _colorStart;
  Color _colorEnd;
  Color _colorPath;
  Color _colorPolygon;

  void InitValues();
  void LoadLevelData() override;
  void SaveLevelData() override;
  sol::state _lua;
  std::unique_ptr<ExamplePathLevelRender> _render;

  friend class ExamplePathLevelRender;
};

} // namespace stemaj

#endif // __EXAMPLEPATHLEVELSTATE_HPP