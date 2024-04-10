#ifndef __PFADFOLLOWER_HPP
#define __PFADFOLLOWER_HPP

#include <game/src/tools/pathfinding.hpp>
#include <vector>

namespace stemaj {

class Pathfollower
{
public:
  void SetPath(const std::vector<Pathfinding::Point>& newPath);
  void SetSpeed(float newSpeed);
  Pathfinding::Point GetCurrentPosition();
  bool MoveTowardsNextPoint();

private:
  std::vector<Pathfinding::Point> path;
  float speed = 0.0f;
  size_t currentPointIndex = size_t(-1);
  Pathfinding::Point currentPosition = Pathfinding::Point(-1,-1);
};

} // namespace

#endif // __PFADFOLLOWER_HPP