#ifndef __LEVELSTATE_HPP
#define __LEVELSTATE_HPP

#include <game/src/state/state.hpp>
#include <game/src/tools/pathfinding.hpp>
#include <game/src/tools/pathfollower.hpp>
#include <memory>
#include <vector>

namespace stemaj {

class LevelRender;

class LevelState : public State
{
public:
  explicit LevelState();
  std::optional<std::unique_ptr<State>> Update(const Input& input, float fElapsedTime) override;
  Render* GetRender() override;
private:
  virtual void LoadLevelData() {}
  virtual void SaveLevelData() {}



  // std::vector<Pathfinding::Point> path;
  // Pathfollower pf;
  // Pathfinding jps;
  // Pathfinding::Point start = Pathfinding::Point(50, 50); // Startpunkt
  // Pathfinding::Point end = Pathfinding::Point(50, 50); // Zielpunkt
  // Pathfinding::Point obj = Pathfinding::Point(50, 50); // Objektpunkt
  //   std::vector<Pathfinding::Point> polygon = { Pathfinding::Point(100,100),
  //     Pathfinding::Point(100,150), Pathfinding::Point(150,150), Pathfinding::Point(150,100) };



private:
  std::unique_ptr<LevelRender> _render;
};

} // namespace stemaj

#endif //__INTROSTATE_HPP