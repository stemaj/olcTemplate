#include <game/src/tools/pfadFollower.hpp>

using namespace stemaj;

void PathFollower::SetPath(const std::vector<Point>& newPath) {
  path = newPath;
  currentPointIndex = 0;
  currentPosition = path[currentPointIndex];
}

void PathFollower::SetSpeed(float newSpeed) {
  speed = newSpeed;
}

Point PathFollower::GetCurrentPosition() {
  return currentPosition;
}

bool PathFollower::MoveTowardsNextPoint() {
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
