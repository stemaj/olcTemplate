#ifndef __INTROSTATE_HPP
#define __INTROSTATE_HPP

#include "olcTemplate/game/guiElements.hpp"
#include <olcTemplate/game/animation.hpp>
#include <olcTemplate/game/input.hpp>
#include <olcTemplate/game/src/state/state.hpp>
#include <olcTemplate/game/coordinates.hpp>
#include <olcTemplate/game/src/tools/fader.hpp>
#include <olcTemplate/game/fonts.hpp>
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

  std::string _font = "";
  float _introTime = 0.0f;
  std::vector<MainMenuColor> _colors;
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

  std::unique_ptr<IntroRender> _render;
};

} // namespace stemaj

#endif //__INTROSTATE_HPP
