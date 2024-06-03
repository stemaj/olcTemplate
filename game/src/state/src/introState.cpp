#include <olcTemplate/game/src/state/introState.hpp>
#include <olcTemplate/game/src/render/introRender.hpp>
#include <olcTemplate/game/src/state/mainMenuState.hpp>
#include <olcTemplate/game/src/render/mainMenuRender.hpp>
#include <optional>
#include <olcTemplate/sdk/imgui-1.90.4/imgui.h>

using namespace stemaj;

IntroState::IntroState() : _render(std::make_unique<IntroRender>())
{
  _introStartTime = std::chrono::steady_clock::now();
}

Render* IntroState::GetRender()
{
  return _render.get();
}

std::optional<std::unique_ptr<State>> IntroState::Update(const Input& input, float fElapsedTime)
{
  ImGui::Begin("Intro Debug");
  ImGui::Text("Mouse Position: (%d, %d)", input.mouseX, input.mouseY);
  ImGui::Text("Duration: (%f)", currentDuration);
  ImGui::End();

  auto now = std::chrono::steady_clock::now();
  currentDuration = std::chrono::duration_cast<std::chrono::milliseconds>(now - _introStartTime).count() / 1000.0f;
  if (currentDuration < introEndDuration)
  {
    if (currentDuration < (introEndDuration * 0.10f))
    {
      _part = Parts::OLCLOGO;
    }
    else if (currentDuration > (introEndDuration * 0.15f) && currentDuration < (introEndDuration * 0.3f))
    {
      _part = Parts::RIEGEL;
    }
    else if (currentDuration > (introEndDuration * 0.35f) && currentDuration < (introEndDuration * 0.5f))
    {
      _part = Parts::DADDY;
    }
    else if (currentDuration > (introEndDuration * 0.55f) && currentDuration < (introEndDuration * 0.70f))
    {
      _part = Parts::VFC;
    }
    else if (currentDuration > (introEndDuration * 0.75f))
    {
      _part = Parts::GAME;
    }
    else
    {
      _part = Parts::BLACK;
    }
    return std::nullopt;
  }
  return std::make_unique<MainMenuState>();
}
