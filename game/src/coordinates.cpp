#include <game/coordinates.hpp>
#define SOL_ALL_SAFETIES_ON 1
#include <sdk/sol2-3.3.0/sol.hpp>

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

template <typename T>
T Coordinates::Distance(const PT<T>& p1, const PT<T>& p2)
{
  return static_cast<T>(std::sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y)));
}

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
