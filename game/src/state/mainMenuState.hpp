#ifndef __MAINMENUSTATE_HPP
#define __MAINMENUSTATE_HPP

#include <olcTemplate/game/src/render/mainMenuRender.hpp>
#include <olcTemplate/game/coordinates.hpp>
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

  std::string _font;
  std::array<float,4> _headerColor = {1.0f,1.0f, 1.0f, 1.0f};

  struct Graphics
  {
    std::string name;
    std::array<float,2> pos;
    std::array<float,2> scale;
  };
  struct Texts
  {
    std::array<float,2> pos;
    std::string text;
  };

  std::vector<Graphics> _graphics;
  std::vector<Texts> _texts;


private:

  sol::state _lua;
  std::unique_ptr<MainMenuRender> _render;
};

} // namespace stemaj

#endif //__MAINMENUSTATE_HPP