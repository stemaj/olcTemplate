#ifndef __MAINMENUSTATE_HPP
#define __MAINMENUSTATE_HPP

#include <olcTemplate/game/src/render/mainMenuRender.hpp>
#include <olcTemplate/game/coordinates.hpp>
#include <olcTemplate/game/fonts.hpp>
#include <string>
#include <olcTemplate/game/input.hpp>
#include <olcTemplate/game/src/state/state.hpp>
#include <vector>
#define SOL_ALL_SAFETIES_ON 1
#include <olcTemplate/sdk/sol2-3.3.0/sol.hpp>

namespace stemaj {

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

  std::vector<MainMenuColor> _colors;
  int _backgroundColorIndex = 0;
  std::vector<MainMenuText> _texts;
  std::vector<MainMenuGraphic> _graphics;

private:
  sol::state _lua;
  std::unique_ptr<MainMenuRender> _render;
};

} // namespace stemaj

#endif //__MAINMENUSTATE_HPP