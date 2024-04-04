#include <game/src/state/mainMenuState.hpp>
#include <game/src/render/mainMenuRender.hpp>
#include <game/src/state/levelState.hpp>
#include <game/src/render/levelRender.hpp>
#include <optional>
#include <sdk/imgui-1.90.4/imgui.h>
#include <vector>

using namespace stemaj;

MainMenuState::MainMenuState() : _render(std::make_unique<MainMenuRender>())
{
  _lua.open_libraries(sol::lib::base, sol::lib::io, sol::lib::math, sol::lib::table);

	try
	{
		_lua.safe_script_file("scripts/mainMenu.lua");
	}
	catch (const sol::error& e)
	{
		std::cout << std::string(e.what()) << std::endl;
	}

  someText = _lua["headerText"].get<std::string>();
  std::vector<float> cppArray = _lua["headerColor"].get<std::vector<float>>();
  for (int i = 0; i < cppArray.size(); i++)
  {
    someColor[i] = cppArray[i];
  }
}

Render* MainMenuState::GetRender()
{
  return _render.get();
}

std::optional<std::unique_ptr<State>> MainMenuState::Update(const Input& input)
{
  ImVec4 color = ImVec4(someColor[0], someColor[1], someColor[2], someColor[3]); // Anfangsfarbe
  ImGui::Begin("Main Menu Debug");
  ImGui::Text("Mouse Position: (%d, %d)", input.mouseX, input.mouseY);
  ImGui::ColorEdit3("Color", (float*)&color);

  someColor[0] = color.x;
  someColor[1] = color.y;
  someColor[2] = color.z;
  someColor[3] = color.w;

  ImGui::End();

  if (input.leftMouseClicked)
  {
    return std::make_unique<LevelState>();
  }
  return std::nullopt;
}
