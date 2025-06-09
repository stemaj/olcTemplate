#ifndef __CUTSCENE_HPP
#define __CUTSCENE_HPP

#include <olcTemplate/game/guiElements.hpp>
#include <olcTemplate/game/input.hpp>
#include <olcTemplate/game/src/state/state.hpp>
#include <olcTemplate/game/coordinates.hpp>
#include <olcTemplate/game/src/tools/fader.hpp>
#include <olcTemplate/game/src/render/renderCutscene.hpp>
#include <olcTemplate/game/fonts.hpp>
#define SOL_ALL_SAFETIES_ON 1
#include <olcTemplate/sdk/sol2-3.3.0/sol.hpp>
#include <string>
#include <memory>

namespace olc {
  class Decal;
}

namespace stemaj {

class Cutscene : public State
{
public:
  explicit Cutscene(const std::string& name, const std::string& tryAgainLevelName = "");
  std::optional<std::unique_ptr<State>> Update(const Input& input, float fElapsedTime) override;
  Render* GetRender() override;
  std::unique_ptr<Fader> _fader;

  std::string _font = "";
  float _cutsceneTime = 0.0f;
  std::vector<MainMenuColor> _colors;
  int _backgroundColorIndex = 0;
  std::vector<IntroText> _texts;
  std::vector<IntroGraphic> _graphics;

  std::vector<int> _activeTextIndicies;
  std::vector<int> _activeGraphicIndicies;

private:
  std::string _name;
  float _currentTime = 0.0f;
  bool _animationRewindedForStartup = false;

  std::string _winCutscene = "";
  std::string _tryAgainLevelName = "";
  sol::state _lua;
  std::unique_ptr<RenderCutscene> _render;
};

} // namespace stemaj

#endif //__CUTSCENE_HPP
