#ifndef __LEVELSTATE_HPP
#define __LEVELSTATE_HPP

#include <game/src/state/state.hpp>
#include <game/src/tools/jumpPointSearch.hpp>
#include <game/src/tools/pfadFollower.hpp>
#include <memory>
#include <vector>

namespace stemaj {

class LevelRender;

class LevelState : public State
{
public:
  explicit LevelState();
  std::optional<std::unique_ptr<State>> Update(const Input& input) override;
  Render* GetRender() override;

  std::vector<Point> path;
  PathFollower pf;
  JumpPointSearch jps;
  Point start = Point(50, 50); // Startpunkt
  Point end = Point(50, 50); // Zielpunkt
  Point obj = Point(50, 50); // Objektpunkt
    std::vector<Point> polygon = { Point(100,100),
      Point(100,150), Point(150,150), Point(150,100) };



private:
  std::unique_ptr<LevelRender> _render;
};

} // namespace stemaj

#endif //__INTROSTATE_HPP