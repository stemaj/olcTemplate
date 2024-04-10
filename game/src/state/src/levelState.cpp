#include <game/src/state/levelState.hpp>
#include "game/src/render/levelRender.hpp"
#include <memory>
#include <optional>
#include <sdk/imgui-1.90.4/imgui.h>

using namespace stemaj;

LevelState::LevelState() : _render(std::make_unique<LevelRender>())
{
  jps.SetGrid(320,240);

}

Render* LevelState::GetRender()
{
  return _render.get();
}

std::optional<std::unique_ptr<State>> LevelState::Update(const Input& input)
{
  if (input.leftMouseClicked)
  {
    end.x = input.mouseX;
    end.y = input.mouseY;
    path = jps.FindPath(start, end);
    pf.SetPath(path);
    pf.SetSpeed(1.0f);
  }

  if (pf.MoveTowardsNextPoint())
  {
    obj = pf.GetCurrentPosition();
  }

  ImGui::Begin("Level Debug");
  ImGui::Text("Mouse Position: (%d, %d)", input.mouseX, input.mouseY);
  ImGui::Text("Startpunkt:  (%d, %d)", start.x, start.y);
  ImGui::Text("Endpunkt:  (%d, %d)", end.x, end.y);
  ImGui::Text("Objekt:  (%d, %d)", obj.x, obj.y);
  ImGui::Text("Path:");
           ImGui::Text("Path:");
            ImGui::Separator();
            if (ImGui::BeginListBox("Coordinates", ImVec2(0, path.size()))) {
                for (const auto& point : path) {
                    ImGui::Text("(%d, %d)", point.x, point.y);
                }
                ImGui::EndListBox();
            }
  ImGui::End();

  return std::nullopt;
}
