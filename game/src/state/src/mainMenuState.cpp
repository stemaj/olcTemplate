#include <memory>
#include <olcTemplate/game/src/state/mainMenuState.hpp>
#include <optional>
#include <olcTemplate/sdk/imgui-1.90.4/imgui.h>
#include <vector>

// entry point for the real game
#include <game/starter.hpp>

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

  _font = _lua["font"].get_or<std::string>("dogica");

  std::vector<float> cppArray = _lua["header_color"].get_or<std::vector<float>>({});
  for (int i = 0; i < cppArray.size(); i++)
  {
    _headerColor[i] = cppArray[i];
  }

  sol::table texts = _lua["texts"];
  for (auto& pair : texts)
  {
    sol::table entry = pair.second;
    Texts t;
    t.pos = { entry[1][1], entry[1][2] };
    t.text = entry[2];
    _texts.push_back(t);
  }

  sol::table graphics = _lua["graphics"];
  for (auto& pair : graphics)
  {
    sol::table entry = pair.second;
    Graphics g;
    g.name = entry[1];
    g.pos = { entry[2][1], entry[2][2] };
    g.scale = { entry[3][1], entry[3][2] };
    _graphics.push_back(g);
  }
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

  auto starter = std::make_unique<Starter>();
  return starter->Update(input, fElapsedTime);
}
