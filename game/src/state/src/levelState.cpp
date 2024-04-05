#include <game/src/state/levelState.hpp>
#include "game/src/render/levelRender.hpp"
#include "game/src/tools/pfadfindung.hpp"
#include <memory>
#include <optional>
#include <sdk/imgui-1.90.4/imgui.h>

using namespace stemaj;

LevelState::LevelState() : _render(std::make_unique<LevelRender>())
{
  // Initialisiere das Gitter
        _grid = { 320, std::vector<int>(240, 0) };

        // Setze ein Hindernis (Polygon) als Beispiel
        for (int i = 100; i < 200; ++i) {
            for (int j = 100; j < 300; ++j) {
                _grid[i][j] = 1; // Setze den Gitterwert auf 1, um das Polygon darzustellen
            }
        }

        // Initialisiere den Pfadfinder mit dem Gitter
        pathfinder = std::make_unique<Pfadfindung>(_grid);
}

Render* LevelState::GetRender()
{
  return _render.get();
}

std::optional<std::unique_ptr<State>> LevelState::Update(const Input& input)
{
  // Bewege das Objekt entlang des Pfads
        if (!path.empty() && pathIndex < path.size()) {
            // Berechne die Richtung zum nächsten Punkt im Pfad
            double dx = path[pathIndex].first - obj_x;
            double dy = path[pathIndex].second - obj_y;
            double dist = std::sqrt(dx * dx + dy * dy);

            // Bewege das Objekt in Richtung des nächsten Punkts im Pfad
            if (dist > 0) {
                double moveDist = speed; //  * fElapsedTime;
                if (moveDist > dist) {
                    // Das Objekt hat den aktuellen Punkt im Pfad erreicht
                    obj_x = path[pathIndex].first;
                    obj_y = path[pathIndex].second;
                    pathIndex++;
                } else {
                    obj_x += static_cast<int>((dx / dist) * moveDist);
                    obj_y += static_cast<int>((dy / dist) * moveDist);
                }
            }
        }
        else{
            path.clear();
            bReachedEnd = false;
            goal_x = -1;
            goal_y = -1;
            isGoalSet = false;
            start_x = obj_x;
            start_y = obj_y;
            pathIndex = 0;
            pathfinder.reset(new Pfadfindung(_grid));
        }



        // Setze den Zielpunkt mit der linken Maustaste
        if (input.leftMouseClicked) {
            goal_x = input.mouseX;
            goal_y = input.mouseY;
            path = pathfinder->FindePfad(start_x, start_y, goal_x, goal_y);
            pathIndex = 0;
            isGoalSet = true;
        }


ImGui::Begin("Level Debug");
  ImGui::Text("Mouse Position: (%d, %d)", input.mouseX, input.mouseY);
  ImGui::Text("Startpunkt:  (%d, %d)", start_x, start_y);
  ImGui::Text("Endpunkt:  (%d, %d)", goal_x, goal_y);
  ImGui::Text("Objekt:  (%d, %d)", obj_x, obj_y);
  ImGui::Checkbox("Is Goal Set", &isGoalSet);
  ImGui::Text("Path:");
           ImGui::Text("Path:");
            ImGui::Separator();
            if (ImGui::BeginListBox("Coordinates", ImVec2(0, 200))) {
                for (const auto& point : path) {
                    ImGui::Text("(%d, %d)", point.first, point.second);
                }
                ImGui::EndListBox();
            }
  ImGui::End();

  return std::nullopt;
}
