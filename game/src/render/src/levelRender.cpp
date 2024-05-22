#include <game/src/render/levelRender.hpp>
#include <game/src/state/levelState.hpp>
#include <game/src/engine/olcPixelGameEngine.h>

using namespace stemaj;

void LevelRender::DoRender(olc::PixelGameEngine* pge, float fElapsedTime, State* state)
{
  auto level = static_cast<LevelState*>(state);

  pge->Clear(olc::RED);

  if (level->fadeState == LevelState::Fade::IN)
  {
    level->fadeTimer += fElapsedTime;   
    float alpha = 1 - (level->fadeTimer / level->fadeDuration);
    if (level->fadeTimer <= level->fadeDuration)
    {
      Fade(pge,alpha);
    }
    else
    {
      level->fadeState = LevelState::Fade::IN_DONE;
      level->fadeTimer = level->fadeDuration;
    }
  }

  if (level->fadeState == LevelState::Fade::OUT)
  {
    level->fadeTimer -= fElapsedTime;   
    float alpha = 1 - (level->fadeTimer / level->fadeDuration);
    if (level->fadeTimer >= 0.0f)
    {
      Fade(pge,alpha);
    }
    else
    {
      level->fadeState = LevelState::Fade::OUT_DONE;
      level->fadeTimer = 0.0f;
    }
  }
}

void LevelRender::Fade(olc::PixelGameEngine* pge, float alpha)
{


  std::cout << alpha << std::endl;
  pge->FillRectDecal({0,0},pge->GetScreenSize(), 
    olc::Pixel(0,0,0,static_cast<uint8_t>(255*alpha)));
}
