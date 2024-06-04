#include <olcTemplate/game/src/state/mainMenuState.hpp>
#include <olcTemplate/game/src/render/mainMenuRender.hpp>
#include <game/src/state/levelState.hpp>
#include <olcTemplate/game/src/render/levelRender.hpp>
#include <optional>
#include <olcTemplate/sdk/imgui-1.90.4/imgui.h>
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

  _headerText = _lua["header_text"].get_or<std::string>("");
  std::vector<float> cppArray = _lua["header_color"].get_or<std::vector<float>>({});
  for (int i = 0; i < cppArray.size(); i++)
  {
    _headerColor[i] = cppArray[i];
  }
  auto pos = _lua["header_position"].get_or<std::array<float,2>>({0.0f,0.0f});
  _headerPos = CO.D(PT<float>{pos[0], pos[1]});
}

Render* MainMenuState::GetRender()
{
  return _render.get();
}

std::optional<std::unique_ptr<State>> MainMenuState::Update(const Input& input, float fElapsedTime)
{
  ImVec4 color = ImVec4(_headerColor[0], _headerColor[1], _headerColor[2], _headerColor[3]);
  ImGui::Begin("Main Menu Debug");
  ImGui::Text("Mouse Position: (%d, %d)", input.mouseX, input.mouseY);
  ImGui::ColorEdit3("Color", (float*)&color);

  _headerColor = { color.x, color.y, color.z, color.w };

  ImGui::End();

  if (input.spacePressed)
  {
    return std::make_unique<LevelState>();
  }
  return std::nullopt;
}
