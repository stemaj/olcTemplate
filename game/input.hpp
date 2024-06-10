#ifndef __INPUT_HPP
#define __INPUT_HPP

namespace stemaj {

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
  bool backSpacePressed;
};

} // namespace stemaj

#endif //__INPUT_HPP