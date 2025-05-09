#ifndef __COORDINATES_HPP
#define __COORDINATES_HPP

#include <cmath>
#include <iomanip>
#include <ostream>
#include <vector>

namespace stemaj {

template <typename T>
struct PT
{
	T x;
	T y;

	// Standardkonstruktor
	PT() : x(T()), y(T()) {}

	// Konstruktor, der Typumwandlungen erlaubt
	template <typename U, typename V>
	PT(U x_, V y_) : x(static_cast<T>(x_)), y(static_cast<T>(y_)) {}

	// Method to convert to another PT type
	template <typename U>
	PT<U> to() const
	{
		return PT<U>(static_cast<U>(x), static_cast<U>(y));
	}

	// Addition
	PT operator+(const PT& other) const
	{
			return PT(x + other.x, y + other.y);
	}

	// Subtraktion
	PT operator-(const PT& other) const
	{
			return PT(x - other.x, y - other.y);
	}

	// Multiplikation (elementweise)
	PT operator*(const PT& other) const
	{
			return PT(x * other.x, y * other.y);
	}

	// Division (elementweise)
	PT operator/(const PT& other) const
	{
			return PT(x / other.x, y / other.y);
	}

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
		os << std::setprecision(3) << "{ x: " << obj.x << ", y: " << obj.y << " }\n";
		return os;
	}

	T mag() const
	{
		return std::sqrt(x * x + y * y);
  };
	PT norm() const
	{
		auto r = 1 / mag();
    return {x * r, y * r};
  };
};

class Coordinates
{
public:

	static Coordinates& get();
	Coordinates(Coordinates const&) = delete;
	void operator=(Coordinates const&) = delete;

	int W;
	int H;
	int P;
	bool F;

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

 
private:
	Coordinates();
	virtual ~Coordinates() {}
};

#define CO Coordinates::get()

} // namespace stemaj

#endif // __COORDINATES_HPP
