#ifndef __LEVELSTATE_HPP
#define __LEVELSTATE_HPP

#include <game/src/state/state.hpp>
#include <game/src/tools/pfadfindung.hpp>
#include <memory>
#include <vector>

namespace stemaj {

class LevelRender;

class LevelState : public State
{
public:
  explicit LevelState();
  std::optional<std::unique_ptr<State>> Update(const Input& input) override;
  Render* GetRender() override;

  int start_x = 50, start_y = 50; // Startpunkt
    int goal_x = -1, goal_y = -1; // Zielpunkt
    std::vector<std::pair<int, int>> path; // Gefundener Pfad
    int pathIndex = 0; // Aktueller Index im Pfad
    double speed = 50.0f; // Geschwindigkeit des Objekts
    int obj_x = start_x, obj_y = start_y; // Standort des Objekts
    bool bReachedEnd = false;

    std::unique_ptr<Pfadfindung> pathfinder;
    bool isGoalSet = false; // Gibt an, ob der Zielpunkt festgelegt wurde

     // Methode zum Auslesen des Standorts des Objekts
    std::pair<int, int> getObjectLocation() const {
        return std::make_pair(obj_x, obj_y);
    }
 
private:
std::vector<std::vector<int>> _grid;
  std::unique_ptr<LevelRender> _render;
};

} // namespace stemaj

#endif //__INTROSTATE_HPP