#ifndef __PFADFOLLOWER_HPP
#define __PFADFOLLOWER_HPP

#include <olcTemplate/game/src/tools/pathfinding.hpp>
#include <vector>

namespace stemaj {

class Pathfollower
{
public:
  void SetPath(const std::vector<PT<int>>& newPath);
  void SetSpeed(float newSpeed);
  PT<int> GetCurrentPosition();
  void MoveTowardsNextPoint();
  bool IsMoving() { return _moving; };

private:
  bool _moving = false;
  std::vector<PT<int>> path;
  float speed = 0.0f;
  size_t currentPointIndex = size_t(-1);
  PT<int> currentPosition = {-1,-1};
};

} // namespace

#endif // __PFADFOLLOWER_HPP