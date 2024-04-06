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
        pge->Draw(p.x,p.y, olc::WHITE);

  // Zeichne das Objekt
       // pge->FillCircle(level->, level->obj_y, 3, olc::RED);

// Zeichne den Zielpunkt
            pge->FillCircle(level->end.x, level->end.y, 4, olc::GREEN);
        
        // Zeichne den Startpunkt
        pge->FillCircle(level->start.x, level->start.y, 5, olc::BLUE);

}
