#include <game/coordinates.hpp>
#define SOL_ALL_SAFETIES_ON 1
#include <sdk/sol2-3.3.0/sol.hpp>
#ifdef RUN_TESTS
#include <sdk/doctest-2.4.11/doctest.h>
#endif

using namespace stemaj;

Coordinates& Coordinates::get()
{
  static Coordinates me;
  return me;
}

Coordinates::Coordinates()
{
  sol::state lua;
  lua.open_libraries(sol::lib::base, sol::lib::io, sol::lib::math, sol::lib::table);
	try
	{
		lua.safe_script_file("scripts/settings.lua");
	}
	catch (const sol::error& e)
	{
		std::cout << std::string(e.what()) << std::endl;
	}

  W = lua["width"].get<int>();
  H = lua["height"].get<int>();
}

PT<int> Coordinates::D(PT<float> relativeCoordinate)
{
  return { int(relativeCoordinate.x * float(W)), int(relativeCoordinate.y * float(H)) };
}

PT<float> Coordinates::R(PT<int> absoluteCoordinate)
{
  return { absoluteCoordinate.x / float(W), absoluteCoordinate.y / float(H) };
}

std::vector<PT<int>> Coordinates::VD(std::vector<PT<float>> relativeCoordinates)
{
  std::vector<PT<int>> ret;
  for (const auto& r : relativeCoordinates)
  {
    ret.push_back(D(r));
  }
  return ret;
}

std::vector<PT<float>> Coordinates::VR(std::vector<PT<int>> absoluteCoordinates)
{
  std::vector<PT<float>> ret;
  for (const auto& a : absoluteCoordinates)
  {
    ret.push_back(R(a));
  }
  return ret;
}

template <typename T>
T Coordinates::Distance(const PT<T>& p1, const PT<T>& p2)
{
  return static_cast<T>(std::sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y)));
}

template int Coordinates::Distance(const PT<int>& p1, const PT<int>& p2);
template float Coordinates::Distance(const PT<float>& p1, const PT<float>& p2);

template <typename T>
PT<T> Coordinates::ClosestPoint(const std::vector<PT<T>>& points, const PT<T>& p)
{
  if (points.empty()) return {0,0};

  auto closest = points[0];
  auto minDistance = Distance(points[0], p);

  for (const auto& point : points)
  {
    auto d = Distance(point, p);
    if (d < minDistance)
    {
      minDistance = d;
      closest = point;
    }
  }
  return closest;
}

template PT<int> Coordinates::ClosestPoint(const std::vector<PT<int>>& points, const PT<int>& p);
template PT<float> Coordinates::ClosestPoint(const std::vector<PT<float>>& points, const PT<float>& p);

template <typename T>
bool Coordinates::IsInsidePolygon(const PT<T> point, const std::vector<PT<T>>& polygon)
{
  //A point is in a polygon if a line from the point to infinity crosses the polygon an odd number of times
  bool odd = false;
  // int totalCrosses = 0; // this is just used for debugging
  //For each edge (In this case for each point of the polygon and the previous one)
  for (int i = 0, j = (int)polygon.size() - 1; i < (int)polygon.size(); i++) { // Starting with the edge from the last to the first node
    //If a line from the point into infinity crosses this edge
    if (((polygon[i].y > point.y) != (polygon[j].y > point.y)) // One point needs to be above, one below our y coordinate
      // ...and the edge doesn't cross our Y corrdinate before our x coordinate (but between our x coordinate and infinity)
      && (point.x < (polygon[j].x - polygon[i].x) * (point.y - polygon[i].y) / (polygon[j].y - polygon[i].y) + polygon[i].x)) {
      // Invert odd
      // System.out.println("Point crosses edge " + (j + 1));
      // totalCrosses++;
      odd = !odd;
    }
    //else {System.out.println("Point does not cross edge " + (j + 1));}
    j = i;
  }
  // System.out.println("Total number of crossings: " + totalCrosses);
  //If the number of crossings was odd, the point is in the polygon
  return odd;
}

template bool Coordinates::IsInsidePolygon(const PT<int> point, const std::vector<PT<int>>& polygon);
template bool Coordinates::IsInsidePolygon(const PT<float> point, const std::vector<PT<float>>& polygon);

template <typename T>
PT<T> Coordinates::RotatePoint(const PT<T>& p, const PT<T>& center, float angle)
{
  float s = std::sin(angle);
  float c = std::cos(angle);

  // Translation zum Ursprung
  float xTrans = p.x - center.x;
  float yTrans = p.y - center.y;
  
  // Rotation
  float xNew = xTrans * c - yTrans * s;
  float yNew = xTrans * s + yTrans * c;
  
  // Translation zurück
  xNew += center.x;
  yNew += center.y;
  return {(T)xNew, (T)yNew};
}

template PT<int> Coordinates::RotatePoint(const PT<int>& p, const PT<int>& center, float angle);
template PT<float> Coordinates::RotatePoint(const PT<float>& p, const PT<float>& center, float angle);


#ifdef RUN_TESTS
TEST_CASE("Rotate Point Test")
{
  // Testpunkt und Rotationszentrum
  PT<float> p = {1.0f, 0.0f};
  PT<float> center = {0.0f, 0.0f};

  SUBCASE("Rotate 90 degrees")
  {
    // Erwartetes Ergebnis
    PT<float> expected = {0.0f, 1.0f};

    // Rotation um 90 Grad im Bogenmaß
    float angle = M_PI / 2.0f;
    
    auto result = CO.RotatePoint(p, center, angle);
    
    // Überprüfen, ob das Ergebnis dem erwarteten Ergebnis entspricht
    CHECK(result.x == doctest::Approx(expected.x).epsilon(1e-6));
    CHECK(result.y == doctest::Approx(expected.y).epsilon(1e-6));
  }

  SUBCASE("Rotate -45 degrees")
  {
    // Erwartetes Ergebnis
    PT<float> expected = {std::sqrt(2.0f) / 2.0f, -std::sqrt(2.0f) / 2.0f};

    // Rotation um -45 Grad im Bogenmaß
    float angle = -M_PI / 4.0f;

    // Rotation durchführen
    auto result = CO.RotatePoint(p, center, angle);

    // Überprüfen, ob das Ergebnis dem erwarteten Ergebnis entspricht
    CHECK(result.x == doctest::Approx(expected.x).epsilon(1e-6));
    CHECK(result.y == doctest::Approx(expected.y).epsilon(1e-6));
  }
}

#endif
