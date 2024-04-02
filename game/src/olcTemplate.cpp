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
  Input input;
  input.mouseX = GetMouseX();
  input.mouseY = GetMouseY();

  std::unique_ptr<Render> render = _game.Update(input);


  return true;
}
