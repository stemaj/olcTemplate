#ifndef __PALETTE_HPP
#define __PALETTE_HPP

#include <array>
#include <string>

namespace olc {

}

namespace stemaj {

class Palette
{
public:
	static Palette& get();
	Palette(Palette const&) = delete;
	void operator=(Palette const&) = delete;

	// returns count of colors
	int Init(const std::string& pal);

	std::array<float,4> ColF(const int index);
	float R(const int index);
	float G(const int index);
	float B(const int index);

private:
  Palette() = default;
  virtual ~Palette() = default;

  std::array<float, 4> hexToRGBA(const std::string& hex);

//  std::vector<std::string> _hexValues = {};
};

#define PA Palette::get()

} // stemaj

#endif // __PALETTE_HPP
