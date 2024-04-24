#include <game/input.hpp>
#include <game/src/render/render.hpp>
#include <game/olcTemplate.hpp>
#include <game/assets.hpp>
#include <game/animation.hpp>
#include <game/fonts.hpp>
#include <sdk/imgui-1.90.4/imgui.h>
#include <chrono>
#include <thread>

using namespace stemaj;
using timePoint = std::chrono::time_point<std::chrono::steady_clock,
  std::chrono::duration<long, std::ratio<1, 1000000000>>>;

bool OlcTemplate::OnUserCreate()
{
  AS.Load();
  AN.Load();
  FT.Load();

  _gameLayer = CreateLayer();
  EnableLayer(_gameLayer, true);
  SetLayerCustomRenderFunction(0, [this](){
    _pgeImgui.ImGui_ImplPGE_Render();});

  return true;
}

void reduceFrameRate(const timePoint& start, const float frameTime)
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

  SetDrawTarget((uint8_t)_gameLayer);

  Input input {GetMouseX(),
    GetMouseY(),
    ImGui::GetIO().WantCaptureMouse ? false : GetMouse(0).bPressed,
    GetKey(olc::W).bHeld,
    GetKey(olc::A).bHeld,
    GetKey(olc::S).bHeld,
    GetKey(olc::D).bHeld,
    };

  _game.Update(input, fElapsedTime);
  _game.Render(this, fElapsedTime);
  _game.UpdateState();

  reduceFrameRate(frameStartTime, 1.0f/60.f); // 60 FPS

  return !GetKey(olc::ESCAPE).bPressed;
}
