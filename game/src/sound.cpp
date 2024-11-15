#include <memory>
#include <olcTemplate/game/sound.hpp>
#include <olcTemplate/sdk/soloud/include/soloud.h>
#include <olcTemplate/sdk/soloud/include/soloud_wav.h>
#include <olcTemplate/game/loadsave.hpp>
#include <thread>

using namespace stemaj;

Sound& Sound::get()
{
  static Sound me;
  return me;
}

Sound::Sound()
{
  LS.Init("scripts/settings.lua", false);
  _soundEnabled = LS.Boolean("sound");

  if (_soundEnabled)
  {
    _soundEngine = std::make_unique<SoLoud::Soloud>();
    _soundEngine->init();
  }
}

Sound::~Sound()
{
  if (_soundEnabled && _soundEngine != nullptr)
  {
    _soundEngine->stopAll();
    _effects.clear();
    _soundEngine->deinit();
  }
}

void Sound::StartMusic(const std::string& filePath, float volume, float fadeInTime)
{
  if (!_soundEnabled || _soundEngine == nullptr)
  {
    return;
  }

  StopMusic();
  while (_soundEngine->getActiveVoiceCount() > 0)
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }

  _music = std::make_unique<SoLoud::Wav>();
  _music->load(filePath.c_str());
  _music->setLooping(true);
  _music->setVolume(volume);

  if (fadeInTime > 0.0f)
  {
    _soundEngine->fadeVolume(_musicHandle, 0.0f, fadeInTime);
  }
  _musicHandle = _soundEngine->play(*_music, volume);
}

void Sound::StopMusic(float fadeOutTime)
{
  if (!_soundEnabled || _soundEngine == nullptr)
  {
    return;
  }

  if (fadeOutTime > 0.0f)
  {
    _soundEngine->fadeVolume(_musicHandle, 0.0f, fadeOutTime);
    _soundEngine->scheduleStop(_musicHandle,
      _soundEngine->getStreamTime(_musicHandle) + fadeOutTime);
  }
  else
  {
    _soundEngine->stop(_musicHandle);
  }
}

void Sound::StartEffect(const std::string& filepath, float volume)
{
  if (!_soundEnabled || _soundEngine == nullptr)
  {
    return;
  }

  _effects.emplace_back(std::make_unique<SoLoud::Wav>());
  _effects[_effects.size()-1]->load(filepath.c_str());
  _effects[_effects.size()-1]->setVolume(volume);
  _soundEngine->play(*_effects[_effects.size()-1]);
}

void Sound::StopAllEffects()
{
  if (!_soundEnabled || _soundEngine == nullptr)
  {
    return;
  }

  for (auto& e : _effects)
  {
    e->stop();
  }
  _effects.clear();
}