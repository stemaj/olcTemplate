#ifndef __PFADFOLLOWER_HPP
#define __PFADFOLLOWER_HPP

#include <game/src/tools/jumpPointSearch.hpp>
#include <vector>
#include <cmath>


namespace stemaj {

  class PathFollower {
  
  public:
    void SetPath(const std::vector<Point>& newPath);
    void SetSpeed(float newSpeed);
    Point GetCurrentPosition();
    bool MoveTowardsNextPoint();

  private:
    std::vector<Point> path;
    float speed = 0.0f;
    size_t currentPointIndex = size_t(-1);
    Point currentPosition = Point(-1,-1);
  };




} // namespace

#endif // __PFADFOLLOWER_HPP