#ifndef __LOADING_HPP
#define __LOADING_HPP

#include <olcTemplate/game/src/state/state.hpp>
#include <olcTemplate/game/src/tools/fader.hpp>

#ifdef __EMSCRIPTEN__
  #include <experimental/coroutine>
  using suspend_never = std::experimental::suspend_never;
#else
  #include <coroutine>
  using suspend_never = std::suspend_never;
#endif

namespace olc {
  class Decal;
}

namespace stemaj {

  using Task = void;
// // Eine einfache Coroutine für asynchrone Aufgaben
// struct Task {
//     struct promise_type {
//         Task get_return_object() { return {}; }
//         suspend_never initial_suspend() { return {}; } 
//         suspend_never final_suspend() noexcept { return {}; } 
//         void return_void() {}
//         void unhandled_exception() { std::terminate(); }
//     };
// };

class Render;
class LoadingRender;

class Loading : public State
{
public:

  explicit Loading();
  std::optional<std::unique_ptr<State>> Update(const Input& input, float fElapsedTime) override;
  Render* GetRender() override;
  void setNext(std::unique_ptr<State> onNext) override {}
  void setAgain(std::unique_ptr<State> onAgain) override {}

  float endTime = 5.0f;
  float timer = 0.0f;
  bool ended = false;
  bool loadingStarted = false;
private:
  bool _firstStart = true;
  bool _loadingStarted = false;

  std::unique_ptr<LoadingRender> _render;
};

} // namespace stemaj

#endif //__LOADING_HPP