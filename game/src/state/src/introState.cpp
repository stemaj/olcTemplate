#include <game/src/state/introState.hpp>
#include "game/src/render/introRender.hpp"
#include "game/src/state/mainMenuState.hpp"
#include <memory>
#include <optional>
#include <sdk/imgui-1.90.4/imgui.h>

using namespace stemaj;

IntroState::IntroState() : _render(std::make_unique<IntroRender>())
{
  _introStartTime = std::chrono::steady_clock::now();
}

Render* IntroState::GetRender()
{
  return _render.get();
}

std::optional<std::unique_ptr<State>> IntroState::Update(const Input& input)
{
  ImGui::Begin("Intro Debug");
  ImGui::Text("Mouse Position: (%d, %d)", input.mouseX, input.mouseY);
  ImGui::Text("Duration: (%f)", currentDuration);
  ImGui::End();

  auto now = std::chrono::steady_clock::now();
  currentDuration = std::chrono::duration_cast<std::chrono::milliseconds>(now - _introStartTime).count() / 1000.0f;
  if (currentDuration < introEndDuration)
  {
    return std::nullopt;
  }
  return std::make_unique<MainMenuState>();
}
