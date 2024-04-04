#ifndef __MAINMENUSTATE_HPP
#define __MAINMENUSTATE_HPP

#include <memory>
#include <string>
#include <game/input.hpp>
#include <game/src/state/state.hpp>
#define SOL_ALL_SAFETIES_ON 1
#include <sdk/sol2-3.3.0/sol.hpp>

namespace stemaj {

class MainMenuRender;

class MainMenuState : public State
{
public:
  explicit MainMenuState();
  std::optional<std::unique_ptr<State>> Update(const Input& input) override;
  Render* GetRender() override;

  std::string someText = "Main Menu";
  int someX = 80;
  int someY = 100;
  std::array<float,4> someColor = {1.0f,1.0f, 1.0f, 1.0f};
private:
  sol::state _lua;
  std::unique_ptr<MainMenuRender> _render;
};

} // namespace stemaj

#endif //__MAINMENUSTATE_HPP