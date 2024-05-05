#ifndef __COORDINATES_HPP
#define __COORDINATES_HPP

#include <ostream>
#include <vector>

namespace stemaj {

template <typename T>
struct PT
{
	T x;
	T y;
  bool operator==(const PT& other) const
	{
		return x == other.x && y == other.y;
	}
  bool operator!=(const PT& other) const
	{
		return x != other.x || y != other.y;
	}
	friend std::ostream& operator<<(std::ostream& os, const PT& obj)
	{
		os << "{ x: " << obj.x << ", y: " << obj.y << " }\n";
		return os;
	}
};

class Coordinates
{
public:

	static Coordinates& get();
	Coordinates(Coordinates const&) = delete;
	void operator=(Coordinates const&) = delete;

	int W;
	int H;

	// some helper functions
	PT<int> D(PT<float> relativeCoordinate);

	PT<float> R(PT<int> absoluteCoordinate);

	std::vector<PT<int>> VD(std::vector<PT<float>> relativeCoordinates);

	std::vector<PT<float>> VR(std::vector<PT<int>> absoluteCoordinates);

	template <typename T>
	T Distance(const PT<T>& p1, const PT<T>& p2);
	
	template <typename T>
	PT<T> ClosestPoint(const std::vector<PT<T>>& points, const PT<T>& p);

	template <typename T>
	bool IsInsidePolygon(const PT<T> point, const std::vector<PT<T>>& polygon);
  
  // Funktion zur Berechnung der Rotation eines Punktes um einen anderen Punkt
  template <typename T>
  PT<T> RotatePoint(const PT<T>& p, const PT<T>& center, float angle);

  // Funktion zur Transformation des Rechtecks
  template <typename T>
  std::array<PT<T>, 4> TransformRectangle(const std::array<PT<T>, 4>& rectangle, const PT<T>& A1, const PT<T>& B1, const PT<T>& A2, const PT<T>& B2);
  
private:
	Coordinates();
	virtual ~Coordinates() {}
};

#define CO Coordinates::get()

} // namespace stemaj

#endif // __COORDINATES_HPP
