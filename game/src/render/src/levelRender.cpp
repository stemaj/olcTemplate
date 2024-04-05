#include <game/src/render/levelRender.hpp>
#include <game/src/state/levelState.hpp>
#include <game/src/engine/olcPixelGameEngine.h>

using namespace stemaj;

void LevelRender::DoRender(olc::PixelGameEngine* pge, float fElapsedTime, State* state)
{
  auto level = static_cast<LevelState*>(state);

  pge->Clear(olc::DARK_RED);

 // Draw Path
    for (const auto& p : level->path)
        pge->Draw(p.first,p.second, olc::WHITE);

  // Zeichne das Objekt
        pge->FillCircle(level->obj_x, level->obj_y, 5, olc::RED);

// Zeichne den Zielpunkt
        if (level->goal_x != -1 && level->goal_y != -1) {
            pge->FillCircle(level->goal_x, level->goal_y, 3, olc::GREEN);
        }

        // Zeichne den Startpunkt
        pge->FillCircle(level->start_x, level->start_y, 3, olc::BLUE);

}
