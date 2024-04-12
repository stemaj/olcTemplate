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
	template <typename T>
	T Distance(const PT<T>& p1, const PT<T>& p2);
	
	template <typename T>
	PT<T> ClosestPoint(const std::vector<PT<T>>& points, const PT<T>& p);

private:
	Coordinates();
	virtual ~Coordinates() {}
};

#define CO Coordinates::get()

} // namespace stemaj

#endif // __COORDINATES_HPP
