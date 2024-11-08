#ifndef __MAINMENUSTATE_HPP
#define __MAINMENUSTATE_HPP

#include <olcTemplate/game/coordinates.hpp>
#include <olcTemplate/game/fonts.hpp>
#include <olcTemplate/game/input.hpp>
#include <olcTemplate/game/src/state/state.hpp>
#define SOL_ALL_SAFETIES_ON 1
#include <olcTemplate/sdk/sol2-3.3.0/sol.hpp>
#include <map>

namespace olc {
  namespace QuickGUI {
    class Manager;
  }
}

namespace stemaj {

class Render;
class MainMenuRender;

class MainMenuState : public State
{
public:
  explicit MainMenuState();
  std::optional<std::unique_ptr<State>> Update(const Input& input, float fElapsedTime) override;
  Render* GetRender() override;

  using MainMenuColor = std::array<int, 4>;
  struct MainMenuText
  {
    std::string text;
    PT<int> pos;
    FontSize fontSize;
    int colorListIndex;
  };
  struct MainMenuGraphic
  {
    std::string file;
    PT<int> pos;
    float scale;
  };

  std::string _font;
	
	
	int colorIndexNormal = 0;
	int colorIndexHover = 0;
	int colorIndexClick = 0;


  std::vector<MainMenuColor> _colors = {};
  int _backgroundColorIndex = 0;
  int _buttonNormalColorIndex = 0;
  int _buttonHoverColorIndex = 0;
  int _buttonClickColorIndex = 0;


  std::vector<MainMenuText> _texts;
  std::vector<MainMenuGraphic> _graphics;
  std::unordered_map<ButtonAction, MainMenuText> _buttons;
	
	ButtonAction _buttonHit = ButtonAction::NO_ACTION;

  std::unique_ptr<olc::QuickGUI::Manager> _guiManager;

private:
  sol::state _lua;
  std::unique_ptr<MainMenuRender> _render;
};

} // namespace stemaj

#endif //__MAINMENUSTATE_HPP
