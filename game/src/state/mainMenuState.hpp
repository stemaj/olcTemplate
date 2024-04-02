#ifndef __MAINMENUSTATE_HPP
#define __MAINMENUSTATE_HPP

#include <memory>
#include <string>
#include <game/input.hpp>
#include <game/src/state/state.hpp>
#include <game/src/render/mainMenuRender.hpp>

namespace stemaj {

class MainMenuState : public State
{
public:
  explicit MainMenuState();
  void Update(const Input& input) override;
  Render* GetRender() override;

  std::string someText = "Main Menu";
  int someX = 80;
  int someY = 100;
  std::string someColor = "white";
private:
  std::unique_ptr<MainMenuRender> _render;
};

} // namespace stemaj

#endif //__MAINMENUSTATE_HPP