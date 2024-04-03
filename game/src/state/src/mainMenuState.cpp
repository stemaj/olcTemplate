#include "game/src/render/mainMenuRender.hpp"
#include <game/src/state/mainMenuState.hpp>
#include <optional>
#include <sdk/imgui-1.90.4/imgui.h>
#include <vector>
#define SOL_ALL_SAFETIES_ON 1
#include <sdk/sol2-3.3.0/sol.hpp>

using namespace stemaj;

MainMenuState::MainMenuState() : _render(std::make_unique<MainMenuRender>())
{
  sol::state lua;
  lua.open_libraries(sol::lib::base, sol::lib::io, sol::lib::math, sol::lib::table);

  // Step 1) Load & Parse File
	try
	{
		lua.safe_script_file("scripts/mainMenu.lua");
		std::cout << "[CPP S1] Lua File read OK!\n";
	}
	catch (const sol::error& e)
	{
		// Something went wrong with loading this script
		std::cout << std::string(e.what()) << "\n";
	}

  std::cout << "[CPP S2] a = " << lua["headerText"].get_or<std::string>("0") << "\n";
  std::vector<float> cppArray = lua["headerColor"].get<std::vector<float>>();

  for (int i = 0; i< cppArray.size(); i++)
  {
    std::cout << cppArray[i];

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
  return std::nullopt;
}
