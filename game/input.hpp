#ifndef __INPUT_HPP
#define __INPUT_HPP

#include <cstdint>
namespace stemaj {

enum ButtonAction : uint8_t
{
	START_GAME,
	OPTION_1,
	OPTION_2,
	OPTION_3,
	OPTION_4,
	OPTION_5,
  OPTION_6,
  OPTION_7,
  OPTION_8,
  OPTION_9,
  OPTION_0,
  BACK,
	NO_ACTION,
};

struct Input
{
  int mouseX;
  int mouseY;
  bool leftMouseClicked;
  bool rightMouseClicked;
  bool middleMouseClicked;
  bool leftMouseHeld;
  bool rightMouseHeld;
  bool middleMouseHeld;
  bool leftMouseReleased;
  bool rightMouseReleased;
  bool middleMouseReleased;
  bool wHold;
  bool aHold;
  bool sHold;
  bool dHold;
  bool pgUpHold;
  bool pgDownHold;
  bool k1Pressed;
  bool k2Pressed;
  bool k3Pressed;
  bool k4Pressed;
  bool k5Pressed;
  bool k6Pressed;
  bool k7Pressed;
  bool k8Pressed;
  bool k9Pressed;
  bool k0Pressed;
  bool spacePressed;
  bool escapePressed;
};

} // namespace stemaj

#endif //__INPUT_HPP
