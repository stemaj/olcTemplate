#ifndef __FADER_HPP
#define __FADER_HPP

#include <cstdint>

namespace stemaj
{

class Fader
{
public:
  enum class FadeState { NONE, FADE_OUT, FADE_IN };
  Fader(const float duration) : fadeDuration(duration) {}

  void StartFadeOut();
  void StartFadeIn();
  bool IsFading() const;
  void Update(float fElapsedTime);
  uint8_t GetAlpha() const;

private:
  FadeState fadeState = FadeState::NONE;
  float fadeTimer = 0.0f;
  float fadeDuration = 0.0f;
};

} // namespace

#endif // __FADER_HPP