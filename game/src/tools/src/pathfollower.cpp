#include "game/src/tools/pathfinding.hpp"
#include <cmath>
#ifdef RUN_TESTS
#include <sdk/doctest-2.4.11/doctest.h>
#endif
#include <game/src/tools/pfadFollower.hpp>

using namespace stemaj;
using Point = stemaj::Pathfinding::Point;

void Pathfollower::SetPath(const std::vector<Point>& newPath) {
  path = newPath;
  currentPointIndex = 0;
  currentPosition = path[currentPointIndex];
}

void Pathfollower::SetSpeed(float newSpeed) {
  speed = newSpeed;
}

Point Pathfollower::GetCurrentPosition() {
  return currentPosition;
}

bool Pathfollower::MoveTowardsNextPoint() {
  if (currentPointIndex >= path.size() - 1) {
    // Already reached the end of the path
    return false;
  }

  Point nextPoint = path[currentPointIndex + 1];

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

  return true;
}

#ifdef RUN_TESTS
TEST_CASE("Testing PfadFollower") {
}
#endif //RUN_TESTS