#ifndef __MAINMENUSTATE_HPP
#define __MAINMENUSTATE_HPP

#include <olcTemplate/game/coordinates.hpp>
#include <olcTemplate/game/fonts.hpp>
#include <olcTemplate/game/input.hpp>
#include <olcTemplate/game/src/state/state.hpp>
#include <olcTemplate/game/src/render/mainMenuRender.hpp>
#include <olcTemplate/game/guiElements.hpp>
#include <unordered_map>

namespace stemaj {

class Render;

class MainMenuState : public State
{
public:
  explicit MainMenuState();
  std::optional<std::unique_ptr<State>> Update(const Input& input, float fElapsedTime) override;
  Render* GetRender() override;

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

private:
  std::unique_ptr<MainMenuRender> _render;
};

} // namespace stemaj

#endif //__MAINMENUSTATE_HPP
