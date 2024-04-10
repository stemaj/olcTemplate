#ifndef __COORDINATES_HPP
#define __COORDINATES_HPP

namespace stemaj {

class Coordinates
{
public:

	static Coordinates& get();
	Coordinates(Coordinates const&) = delete;
	void operator=(Coordinates const&) = delete;

	int W;
	int H;

private:
	Coordinates();
	virtual ~Coordinates() {}
};

#define CO Coordinates::get()

} // namespace stemaj

#endif // __COORDINATES_HPP
