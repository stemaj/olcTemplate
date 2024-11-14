#ifndef __GUI_HPP
#define __GUI_HPP

#include "olcTemplate/game/guiElements.hpp"
#include "olcTemplate/game/input.hpp"
#include <memory>
#include <string>

namespace olc {
  class Font;
  class PixelGameEngine;
}

namespace stemaj {


class Gui
{
public:
  Gui();
  virtual ~Gui();

  void setColNormal(int r, int g, int b, int alpha);
  void setColHover(int r, int g, int b, int alpha);
  void setColClick(int r, int g, int b, int alpha);

  void prepareTextButton(ButtonAction ba, const std::string& text,
    const std::string& fontName, const FontSize fontSize,
    const MainMenuColor color, PT<int> coord, int buttonDelta);
  void prepareImageButton(ButtonAction ba, const std::string& fileName, 
    PT<int> coord, int buttonDelta);

  ButtonAction pressedOn();

  void Update(olc::PixelGameEngine* pge);

private:
  class GuiImpl;
  std::unique_ptr<GuiImpl> _impl;
};

}

#endif // __GUI_HPP