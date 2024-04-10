#ifndef __EXAMPLEPATHLEVELSTATE_HPP
#define __EXAMPLEPATHLEVELSTATE_HPP

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
  struct Grid
  {
    int width;
    int height;
  };
  Grid _grid;
  struct GridPoint
  {
    int x;
    int y;
  };
  GridPoint _start;
  struct Color
  {
    int r;
    int g;
    int b;
    int alpha;
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
};

} // namespace stemaj

#endif // __EXAMPLEPATHLEVELSTATE_HPP