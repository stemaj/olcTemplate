#ifndef __GUI_HPP
#define __GUI_HPP

#include "olcTemplate/game/guiElements.hpp"
#include "olcTemplate/game/input.hpp"
#include <memory>
#include <string>
#include <unordered_map>

namespace olc {
  class Font;
  class Renderable;
  class PixelGameEngine;
  namespace QuickGUI {
    class Manager;
    class BaseControl;
  }
}

namespace stemaj {


using RenderedText = std::shared_ptr<olc::Renderable>;
using RenderedControl = std::shared_ptr<olc::QuickGUI::BaseControl>;

class Gui
{
public:
  explicit Gui();
  virtual ~Gui() = default;
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
  std::shared_ptr<olc::QuickGUI::Manager> guiManager;
  std::unordered_map<ButtonAction, RenderedControl> _controls;
  std::unordered_map<ButtonAction, RenderedText> _texts;
  std::vector<std::pair<ButtonAction, std::shared_ptr<olc::Renderable>>> rends;
};

}

#endif // __GUI_HPP