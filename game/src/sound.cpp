#include <game/sound.hpp>
#include <sdk/soloud/include/soloud.h>
#include <sdk/soloud/include/soloud_wav.h>

using namespace stemaj;

Sound& Sound::get()
{
  static Sound me;
  return me;
}

//#define _SOUND

Sound::~Sound()
{
#ifndef _SOUND
    return;
#endif
  _soundEngine->deinit();
}

void Sound::Play(const std::string& name)
{
#ifndef _SOUND
  return;
#endif
  if (name.empty() || _currentlyPlaying == name)
  {
    return;
  }

  if (!_engineInitialized)
  {
    _soundEngine = std::make_unique<SoLoud::Soloud>();
    _soundEngine->init();
    _sample = std::make_unique<SoLoud::Wav>();
    _engineInitialized = true;
  }

  _soundEngine->stopAll();
  _sample->load((std::string("./assets/wav/") + name + std::string(".wav")).c_str());
  _sample->setLooping(true);
  _soundEngine->play(*_sample);
  _currentlyPlaying = name;
}
