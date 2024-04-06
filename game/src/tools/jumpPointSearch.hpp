#ifndef __PFADFINDUNG_HPP
#define __PFADFINDUNG_HPP

#include <cmath>
#include <memory>
#include <vector>

#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <unordered_set>

namespace stemaj {


  struct Point {
    int x, y;
    Point(int _x, int _y) : x(_x), y(_y) {}
  };



  class JumpPointSearch {

   
 
  public:
 
    void SetGrid(int height, int width);
    void SetPolygon(std::vector<Point> poly);
    void Clear();
    std::vector<Point> FindPath(Point start, Point end);
  private:
    int gridHeight = 0, gridWidth = 0;
    std::vector<std::vector<bool>> obstacles;
    std::vector<Point> polygon;

    std::vector<Point> calculateNeighbors(Point point);
    bool isValidPoint(Point point);
    Point calculateEndPoint(Point point);

  };



 /* int main() {
    JumpPointSearch jps;
    jps.SetGrid(10, 10);

    std::vector<Point> polygon = { Point(3, 3), Point(3, 4), Point(4, 4), Point(4, 3) };
    jps.SetPolygon(polygon);

    Point start(0, 0);
    Point end(9, 9);

    std::vector<Point> path = jps.FindPath(start, end);

    std::cout << "Path: ";
    for (auto point : path) {
      std::cout << "(" << point.x << "," << point.y << ") ";
    }
    std::cout << std::endl;

    return 0;
  }*/


} // namespace stemaj

#endif //__PFADFINDUNG_HPP