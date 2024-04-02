#include <X11/Xlib.h>
#include <game/input.hpp>
#include <game/src/render/render.hpp>
#include <game/olcTemplate.hpp>
#include <chrono>
#include <thread>

using namespace stemaj;

bool OlcTemplate::OnUserCreate()
{
  return true;
}

void reduceFrameRate(std::chrono::time_point<std::chrono::steady_clock, std::chrono::duration<long, std::ratio<1, 1000000000>>> start, float frameTime)
{
  auto now = std::chrono::steady_clock::now();
  auto frameDuration = std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count() / 1000.0f;
  if (frameDuration < frameTime)
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>((frameTime - frameDuration) * 1000)));
  }
}

bool OlcTemplate::OnUserUpdate(float fElapsedTime)
{
  auto frameStartTime = std::chrono::steady_clock::now();

  Input input {GetMouseX(),
  GetMouseY(),
  GetMouse(0).bPressed};

  _game.Update(input);
  _game.Render(this, fElapsedTime);

  reduceFrameRate(frameStartTime, 1.0f/60.f); // 60 FPS

  return !GetKey(olc::ESCAPE).bPressed;
}
