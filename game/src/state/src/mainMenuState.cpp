#include <memory>
#include <olcTemplate/game/src/state/mainMenuState.hpp>
#include <olcTemplate/sdk/imgui-1.90.4/imgui.h>

// entry point for the real game
#include <game/starter.hpp>
#include <optional>
#include <string>

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
  _colors = _lua["colors"].get<std::vector<MainMenuColor>>();
  _backgroundColorIndex = _lua["background_color"].get_or(0);

  sol::table textsTable = _lua["texts"];
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

  sol::table graphicsTable = _lua["graphics"];
  for (size_t i = 1; i <= graphicsTable.size(); i++)
  {
    sol::table t = graphicsTable[i];
    auto p = t.get<std::array<float, 2>>(2);
    _graphics.push_back({
      t.get<std::string>(1),
      CO.D({p[0],p[1]}),
      t.get<float>(3) });
  }

  sol::table buttonsTable = _lua["buttons"];
  for (auto& pair : buttonsTable)
  {
    int key = pair.first.as<int>();
    sol::table values = pair.second;
    auto p = values.get<std::array<float, 2>>(2);
    _buttons[(ButtonAction)key] = {
      values[1],
      CO.D({p[0],p[1]}),
      values[3],
      values[4]
    };
  }
}

Render* MainMenuState::GetRender()
{
  return _render.get();
}

std::optional<std::unique_ptr<State>> MainMenuState::Update(const Input& input, float fElapsedTime)
{
  std::array<float,4> colorOne = { _colors[0][0] / 255.0f, _colors[0][1] / 255.0f, 
                                   _colors[0][2] / 255.0f, _colors[0][3] / 255.0f };
#if defined(STEMAJ_DEBUG)
  ImVec4 color = ImVec4(colorOne[0], colorOne[1], colorOne[2], colorOne[3]);
  ImGui::Begin("Main Menu Debug");
  ImGui::Text("Mouse Position: (%d, %d)", input.mouseX, input.mouseY);
  ImGui::ColorEdit3("Color", (float*)&color);
#endif

  _colors[0] = { int(colorOne[0] * 255.0f), int(colorOne[1] * 255.0f),
                 int(colorOne[2] * 255.0f), int(colorOne[3] * 255.0f) };

#if defined(STEMAJ_DEBUG)
  ImGui::End();
#endif

  if (_startGame)
  {
    auto starter = std::make_unique<Starter>();
    return starter->Update(input, fElapsedTime);
  }
  return std::nullopt;
}
