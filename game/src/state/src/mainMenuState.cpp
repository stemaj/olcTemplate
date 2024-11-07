#include "olcTemplate/game/fonts.hpp"
#include "olcTemplate/game/input.hpp"
#include "sol.hpp"
#include <memory>
#include <olcTemplate/game/src/engine/olcPGEX_QuickGUI.h>
#include <olcTemplate/game/src/render/mainMenuRender.hpp>
#include <olcTemplate/game/src/state/mainMenuState.hpp>
#include <olcTemplate/sdk/imgui-1.90.4/imgui.h>
#include <olcTemplate/game/sound.hpp>
#include <olcTemplate/game/src/engine/olcPGEX_QuickGUI.h>

// entry point for the real game
#include <game/starter.hpp>
#include <optional>
#include <string>

using namespace stemaj;

MainMenuState::MainMenuState() : _render(std::make_unique<MainMenuRender>())
{
  SO.StartMusic("./olcTemplate/assets/wav/hard-rock-logo-108960.mp3", 0.5f);

  _lua.open_libraries(sol::lib::base, sol::lib::io, sol::lib::math, sol::lib::table);

  try
  {
    _lua.safe_script_file("scripts/mainMenu.lua");
  }
  catch (const sol::error& e)
  {
    std::cout << std::string(e.what()) << std::endl;
  }

  _font = _lua["font"].get_or<std::string>("dogica");
  _colors = _lua["colors"].get_or<std::vector<MainMenuColor>>({std::array<int, 4>({255,255,255,255})});
  _backgroundColorIndex = _lua["background_color"].get_or(0);
  _buttonNormalColorIndex = _lua["button_normal_color"].get_or(0);
  _buttonHoverColorIndex = _lua["button_hover_color"].get_or(0);
  _buttonClickColorIndex = _lua["button_click_color"].get_or(0);

  sol::table textsTable = _lua["texts"].get_or(sol::table(_lua,sol::create));
  for (size_t i = 1; i <= textsTable.size(); i++)
  {
    sol::table t = textsTable[i];
    auto p = t.get<std::array<float, 2>>(2);
    _texts.push_back({
      t.get<std::string>(1),
      CO.D({p[0],p[1]}),
      (FontSize)t.get<int>(3),
      t.get<int>(4) });
  }

  sol::table graphicsTable = _lua["graphics"].get_or(sol::table(_lua,sol::create));
  for (size_t i = 1; i <= graphicsTable.size(); i++)
  {
    sol::table t = graphicsTable[i];
    auto p = t.get_or<std::array<float, 2>>(2,{});
    _graphics.push_back({
      t.get_or<std::string>(1,""),
      CO.D({p[0],p[1]}),
      t.get_or(3,0.0f) });
  }

  sol::table buttonsTable = _lua["buttons"].get_or(sol::table(_lua,sol::create));
  for (auto& [key, values] : buttonsTable)
  {
    //int key = pair.first.as<int>();
    //sol::table values = pair.second;
    auto p = ((sol::table)values).get_or<std::array<float, 2>>(2,{});
    _buttons[(ButtonAction)key.as<int>()] = {
      ((sol::table)values).get_or<std::string>(1,""),
      CO.D({p[0],p[1]}),
      ((sol::table)values).get_or(3,(FontSize)0),
      ((sol::table)values).get_or(4,0),
    };
  }
}

Render* MainMenuState::GetRender()
{
  return _render.get();
}

std::optional<std::unique_ptr<State>> MainMenuState::Update(const Input& input, float fElapsedTime)
{
//   std::array<float,4> colorOne = { _colors[0][0] / 255.0f, _colors[0][1] / 255.0f, 
//                                    _colors[0][2] / 255.0f, _colors[0][3] / 255.0f };
// #if defined(STEMAJ_DEBUG)
//   ImVec4 color = ImVec4(colorOne[0], colorOne[1], colorOne[2], colorOne[3]);
//   ImGui::Begin("Main Menu Debug");
//   ImGui::Text("Mouse Position: (%d, %d)", input.mouseX, input.mouseY);
//   ImGui::ColorEdit3("Color", (float*)&color);
// #endif

//   _colors[0] = { int(colorOne[0] * 255.0f), int(colorOne[1] * 255.0f),
//                  int(colorOne[2] * 255.0f), int(colorOne[3] * 255.0f) };

// #if defined(STEMAJ_DEBUG)
//   ImGui::End();
// #endif
	
	if (input.spacePressed) _buttonHit = START_GAME;
  if (input.k1Pressed) _buttonHit = OPTION_1;
	if (input.k2Pressed) _buttonHit = OPTION_2;
	if (input.k3Pressed) _buttonHit = OPTION_3;
	if (input.k4Pressed) _buttonHit = OPTION_4;
	if (input.k5Pressed) _buttonHit = OPTION_5;
  if (input.k6Pressed) _buttonHit = OPTION_6;

	return Starter::SwitchState(_buttonHit);
}
