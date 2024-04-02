#include <X11/Xlib.h>
#include <game/input.hpp>
#include <game/src/render/render.hpp>
#include <game/olcTemplate.hpp>
#include <memory>

using namespace stemaj;

bool OlcTemplate::OnUserCreate()
{
  return true;
}

bool OlcTemplate::OnUserUpdate(float fElapsedTime)
{
  Input input {GetMouseX(),
    GetMouseY(),
    GetMouse(0).bPressed};

  _game.Update(input);
  _game.Render(this, fElapsedTime);

  return !GetKey(olc::ESCAPE).bPressed;
}
