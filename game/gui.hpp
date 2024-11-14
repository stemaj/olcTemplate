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
  bool created() const { return _created; }
  void setCreated() { _created = true; }

  void prepareText(const ButtonAction ba, const std::string& text,
    const std::string& fontName, const FontSize fontSize, const MainMenuColor color);
  void prepareControl(ButtonAction key, PT<int> coord, int buttonDelta);

  ButtonAction buttonActionPressed() const;

  void Update(olc::PixelGameEngine* pge);

  void createImageButton(const std::string& name, float x, float y, int fontDelta);
  bool backButtonPressed();

private:
  bool _created = false;

  class GuiImpl;
  std::unique_ptr<GuiImpl> _impl;
};

}

#endif // __GUI_HPP