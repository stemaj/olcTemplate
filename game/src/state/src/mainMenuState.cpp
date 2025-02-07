#include "olcTemplate/game/input.hpp"
#include "olcTemplate/game/loadsave.hpp"
#include <memory>
#include <olcTemplate/game/src/state/mainMenuState.hpp>
#include <olcTemplate/sdk/imgui-1.90.4/imgui.h>
#include <olcTemplate/game/sound.hpp>
#include <olcTemplate/game/guiElements.hpp>

// entry point for the real game
#include <game/starter.hpp>
#include <optional>
#include <string>

using namespace stemaj;

MainMenuState::MainMenuState() : _render(std::make_unique<MainMenuRender>())
{
  SO.StartMusic("./olcTemplate/assets/wav/hard-rock-logo-108960.mp3", 0.5f);

  LS.Init("scripts/mainMenu.lua", false);
  _font = LS.String("font", "dogica");
  _colors = LS.Colors();
  _backgroundColorIndex = LS.Int("background_color");
  _buttonNormalColorIndex = LS.Int("button_normal_color");
  _buttonHoverColorIndex = LS.Int("button_hover_color");
  _buttonClickColorIndex = LS.Int("button_click_color");
  _texts = LS.Texts();
  _graphics = LS.Graphics();
  _buttons = LS.ButtonTexts();
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
  if (input.k7Pressed) _buttonHit = OPTION_7;
  if (input.k8Pressed) _buttonHit = OPTION_8;
  if (input.k9Pressed) _buttonHit = OPTION_9;
  if (input.k0Pressed) _buttonHit = OPTION_0;

	return Starter::SwitchState(_buttonHit);
}
