#ifndef __LEVELSTATE_HPP
#define __LEVELSTATE_HPP

#include <olcTemplate/game/src/tools/fader.hpp>
#include <olcTemplate/game/src/state/state.hpp>
#include <olcTemplate/game/src/engine/olcUTIL_Camera2D.h>
#include <memory>

namespace stemaj {

class Render;
class LevelRender;

class LevelState : public State
{
public:
  explicit LevelState();
  std::optional<std::unique_ptr<State>> Update(const Input& input,
    float fElapsedTime) override;
  Render* GetRender() override;
  Fader _fader;

protected:
  std::optional<std::unique_ptr<State>> ChangeLevel(
    const Input& input, float fElapsedTime);

  void playMusic(const std::string& filePath, const float fadeTime = 0.0f);
  void stopMusic(const float fadeTime = 0.0f);
  void playEffect(const std::string& filePath);
  void stopAllEffects();

  olc::utils::Camera2D _camera;
  bool _cameraConfigured = false;

private:
  virtual void LoadLevelData() {}
  virtual void SaveLevelData() {}
private:
  std::unique_ptr<LevelRender> _render;
};

} // namespace stemaj

#endif //__INTROSTATE_HPP
