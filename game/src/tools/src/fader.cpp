#include <olcTemplate/game/src/tools/fader.hpp>

using namespace stemaj;

void Fader::StartFadeOut()
{
  fadeState = FadeState::FADE_OUT;
  fadeTimer = 0.0;
}

void Fader::StartFadeIn()
{
  fadeState = FadeState::FADE_IN;
  fadeTimer = 0.0;  
}

bool Fader::IsFading() const
{
  return fadeState != FadeState::NONE;
}

void Fader::Update(float fElapsedTime)
{
  if (fadeState == FadeState::NONE) return;

  fadeTimer += fElapsedTime;
  if (fadeTimer >= fadeDuration)
  {
    fadeTimer = 0.0f;
    fadeState = FadeState::NONE;
  }
}

uint8_t Fader::GetAlpha() const
{
  float alpha = 0.0;
  if (fadeState == FadeState::FADE_OUT)
  {
    alpha = fadeTimer / fadeDuration;
  }
  else if (fadeState == FadeState::FADE_IN)
  {
    alpha = 1 - (fadeTimer / fadeDuration);
  }
  return static_cast<uint8_t>(255 * alpha);
}
