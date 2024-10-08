#include <cmath>
#ifdef RUN_TESTS
#include <olcTemplate/sdk/doctest-2.4.11/doctest.h>
#endif
#include <olcTemplate/game/src/tools/pathfollower.hpp>

using namespace stemaj;

void Pathfollower::SetPath(const std::vector<PT<int>>& newPath) {
  path = newPath;
  currentPointIndex = path.empty() ? -1 : 0;
  currentPosition = path.empty() ? PT<int>{-1, -1} : path[currentPointIndex];
}

void Pathfollower::SetSpeed(float newSpeed) {
  speed = newSpeed;
}

PT<int> Pathfollower::GetCurrentPosition() {
  return currentPosition;
}

void Pathfollower::MoveTowardsNextPoint() {
  if (currentPointIndex >= path.size() - 1) {
    // Already reached the end of the path
    _moving = false;
  }

  PT<int> nextPoint = path[currentPointIndex + 1];

  // Calculate distance to next point
  float deltaX = nextPoint.x - currentPosition.x;
  float deltaY = nextPoint.y - currentPosition.y;
  float distanceToNextPoint = sqrt(deltaX * deltaX + deltaY * deltaY);

  if (distanceToNextPoint <= speed) {
    // Move directly to next point
    currentPosition = nextPoint;
    ++currentPointIndex;
  }
  else {
    // Move towards next point based on speed
    float ratio = speed / distanceToNextPoint;
    currentPosition.x += ratio * deltaX;
    currentPosition.y += ratio * deltaY;
  }

  _moving = true;
}

#ifdef RUN_TESTS
TEST_CASE("Testing PfadFollower") {
}
#endif //RUN_TESTS