#ifndef __INTROSTATE_HPP
#define __INTROSTATE_HPP

#include <olcTemplate/game/animation.hpp>
#include <olcTemplate/game/input.hpp>
#include <olcTemplate/game/src/state/state.hpp>
#include <olcTemplate/game/coordinates.hpp>
#include <olcTemplate/game/src/tools/fader.hpp>
#include <olcTemplate/game/fonts.hpp>
#define SOL_ALL_SAFETIES_ON 1
#include <olcTemplate/sdk/sol2-3.3.0/sol.hpp>
#include <string>
#include <memory>

namespace olc {
  class Decal;
}

namespace stemaj {

class Render;
class IntroRender;

class IntroState : public State
{
public:
  explicit IntroState();
  std::optional<std::unique_ptr<State>> Update(const Input& input, float fElapsedTime) override;
  Render* GetRender() override;
  std::unique_ptr<Fader> _fader;

  using IntroColor = std::array<int, 4>;
  using IntroAnimations = std::string;
  struct IntroText
  {
    std::string text;
    PT<int> pos;
    FontSize fontSize;
    float startTime;
    float endTime;
    int colorListIndex;
  };
  struct IntroGraphic
  {
    std::string file;
    PT<int> pos;
    float scale;
    float startTime;
    float endTime;
  };

  std::string _font = "";
  float _introTime = 0.0f;
  std::vector<IntroColor> _colors;
  int _backgroundColorIndex = 0;
  std::vector<IntroText> _texts;
  std::vector<IntroGraphic> _graphics;
  std::vector<IntroAnimations> _animations;

  std::vector<Sheet> _sheets;

  std::vector<int> _activeTextIndicies;
  std::vector<int> _activeGraphicIndicies;

private:
  float _currentTime = 0.0f;
  bool _animationRewindedForStartup = false;

  sol::state _lua;
  std::unique_ptr<IntroRender> _render;
};

} // namespace stemaj

#endif //__INTROSTATE_HPP
