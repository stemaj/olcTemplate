#ifndef __GUIELEMENTS_HPP
#define __GUIELEMENTS_HPP

#include <cstdint>
#include <array>
#include <olcTemplate/game/coordinates.hpp>

namespace stemaj {

enum class FontSize
{
	NORMAL = 0,
	SMALL = 1,
	BIG = 2,
	SMALLER = 3,
	SMALLEST = 4,
	BIGGER = 5,
	BIGGEST = 6,
	COUNT = 7
};

using IntroAnimations = std::string;
using MainMenuColor = std::array<uint8_t, 4>;
struct MainMenuText
{
  std::string text;
  PT<int> pos;
  FontSize fontSize;
  int colorListIndex;
	int buttonDelta;
};
struct IntroText
{
	std::string text;
	PT<int> pos;
	FontSize fontSize;
	float startTime;
	float endTime;
	int colorListIndex;
};

struct MainMenuGraphic
{
  std::string file;
  PT<int> pos;
  float scale;
	int buttonDelta;
};
struct IntroGraphic
{
	std::string file;
	PT<int> pos;
	float scale;
	float startTime;
	float endTime;
};

} // namespace stemaj

#endif // __GUIELEMENTS_HPP