#include <game/src/tools/jumpPointSearch.hpp>

using namespace stemaj;

void JumpPointSearch::SetGrid(int height, int width) {
  gridHeight = height;
  gridWidth = width;
  obstacles.resize(height, std::vector<bool>(width, false));
}

void JumpPointSearch::SetPolygon(std::vector<Point> poly) {
  polygon = poly;
  for (auto point : polygon) {
    if (point.x >= 0 && point.x < gridHeight && point.y >= 0 && point.y < gridWidth)
      obstacles[point.x][point.y] = true;
  }
}

void JumpPointSearch::Clear() {
  obstacles.clear();
  polygon.clear();
}

bool JumpPointSearch::isValidPoint(Point point) {
  if (point.x < 0 || point.x >= gridHeight || point.y < 0 || point.y >= gridWidth || obstacles[point.x][point.y])
    return false;
  return true;
}

std::vector<Point> JumpPointSearch::calculateNeighbors(Point point) {
  std::vector<Point> neighbors;
  int dx[4] = { -1, 1, 0, 0 };
  int dy[4] = { 0, 0, -1, 1 };

  for (int i = 0; i < 4; ++i) {
    Point neighbor(point.x + dx[i], point.y + dy[i]);
    if (isValidPoint(neighbor))
      neighbors.push_back(neighbor);
  }

  return neighbors;
}

Point stemaj::JumpPointSearch::calculateEndPoint(Point point) {
  std::queue<Point> q;
  std::unordered_set<int> visited;
  q.push(point);

  while (!q.empty()) {
    Point current = q.front();
    q.pop();

    if (isValidPoint(current))
      return current;

    visited.insert(current.x * gridWidth + current.y);

    std::vector<Point> neighbors = calculateNeighbors(current);
    for (Point neighbor : neighbors) {
      int hash = neighbor.x * gridWidth + neighbor.y;
      if (visited.find(hash) == visited.end()) {
        q.push(neighbor);
      }
    }
  }

  // Shouldn't reach here if there's a valid endpoint
  return Point(-1, -1);
}

std::vector<Point> JumpPointSearch::FindPath(Point start, Point end) {
  std::vector<Point> path;
  path.push_back(start);

  Point current = start;
  while (current.x != end.x || current.y != end.y) {
    current = calculateEndPoint(current);
    path.push_back(current);
  }

  return path;
}
