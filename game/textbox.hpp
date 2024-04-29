#ifndef __TEXTBOX_HPP
#define __TEXTBOX_HPP

#include <game/fonts.hpp>
#include <game/coordinates.hpp>
#include <array>

namespace olc {
	class Decal;
}

namespace stemaj {

enum class TextBoxLocation : uint8_t
{
  NORMAL = 0,
  UPPERLEFT = 1,
  LOWERRIGHT = 2,
	COUNT = 3
};

class TextBox
{
public:
	explicit TextBox(const std::string& text,
									 const PT<int> position,
									 const TextBoxLocation location,
									 const std::string& fontName,
									 const FontSize fontSize);

	olc::Decal* Decal();

	std::string _text = "stemaj Template";
	PT<int> _boxUpperLeft = {0,0 };
	PT<int> _frameboxSize = {0,0 };
	PT<int> _frameboxUpperLeft = {0,0 };
	TextBoxLocation _location = TextBoxLocation::NORMAL;
	std::array<PT<int>, 4> _points;

private:
};
  
} // namespace stemaj

#endif // __TEXTBOX_HPP
