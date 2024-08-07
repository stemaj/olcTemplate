#include <olcTemplate/game/input.hpp>
#include <olcTemplate/game/src/render/render.hpp>
#include <olcTemplate/game/olcTemplate.hpp>
#include <olcTemplate/game/assets.hpp>
#include <olcTemplate/game/animation.hpp>
#include <olcTemplate/game/fonts.hpp>
#include <olcTemplate/sdk/imgui-1.90.4/imgui.h>
#include <chrono>
#include <thread>

using namespace stemaj;
using timePoint = std::chrono::time_point<std::chrono::steady_clock,
  std::chrono::duration<long, std::ratio<1, 1000000000>>>;

bool OlcTemplate::OnUserCreate()
{
  std::cout << "Now\n";
  AS.Load();
  AN.Load();
  FT.Load();
  std::cout << "Now 2\n";

#if defined(STEMAJ_DEBUG)
  _gameLayer = CreateLayer();
  EnableLayer(_gameLayer, true);
#if defined(__APPLE__)
	_pgeImgui.ImGui_ImplPGE_Init();
#endif
  SetLayerCustomRenderFunction(0, [this](){
    _pgeImgui.ImGui_ImplPGE_Render();});
#endif //STEMAJ_DEBUG

  return true;
}

void reduceFrameRate(const timePoint& start, const float frameTime)
{
  auto now = std::chrono::steady_clock::now();
  auto frameDuration = std::chrono::duration_cast<std::chrono::milliseconds>
    (now - start).count() / 1000.0f;
  if (frameDuration < frameTime)
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(
      static_cast<int>((frameTime - frameDuration) * 1000)));
  }
}

bool OlcTemplate::OnUserUpdate(float fElapsedTime)
{
  auto frameStartTime = std::chrono::steady_clock::now();
  bool wck = false;
  bool wcm = false;

#if defined(STEMAJ_DEBUG)
  SetDrawTarget((uint8_t)_gameLayer);
  wck = ImGui::GetIO().WantCaptureKeyboard;
  wcm = ImGui::GetIO().WantCaptureMouse;
#endif

  Input input {GetMouseX(), GetMouseY(),
    wcm ? false : GetMouse(0).bPressed,
    wck ? false : (GetKey(olc::W).bHeld || GetKey(olc::UP).bHeld),
    wck ? false : (GetKey(olc::A).bHeld || GetKey(olc::LEFT).bHeld),
    wck ? false : (GetKey(olc::S).bHeld || GetKey(olc::DOWN).bHeld),
    wck ? false : (GetKey(olc::D).bHeld || GetKey(olc::RIGHT).bHeld),
    wck ? false : GetKey(olc::K1).bPressed,
    wck ? false : GetKey(olc::K2).bPressed,
    wck ? false : GetKey(olc::K3).bPressed,
    wck ? false : GetKey(olc::K4).bPressed,
    wck ? false : GetKey(olc::K5).bPressed,
    wck ? false : GetKey(olc::SPACE).bPressed,
    wck ? false : GetKey(olc::ESCAPE).bPressed,
    };

  _game.Update(input, fElapsedTime);
  _game.Render(this, fElapsedTime);
  _game.UpdateState();

  reduceFrameRate(frameStartTime, 1.0f/60.f); // 60 FPS

  return !GetKey(olc::F12).bPressed;
}
