#ifndef __INPUT_HPP
#define __INPUT_HPP

namespace stemaj {

enum ButtonAction
{
	START_GAME,
	OPTION_1,
	OPTION_2,
	OPTION_3,
	OPTION_4,
	OPTION_5,
	NO_ACTION,
};

struct Input
{
  int mouseX;
  int mouseY;
  bool leftMouseClicked;
  bool wHold;
  bool aHold;
  bool sHold;
  bool dHold;
  bool k1Pressed;
  bool k2Pressed;
  bool k3Pressed;
  bool k4Pressed;
  bool k5Pressed;
  bool spacePressed;
  bool escapePressed;
};

} // namespace stemaj

#endif //__INPUT_HPP
