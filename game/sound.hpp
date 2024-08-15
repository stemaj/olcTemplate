#ifndef __SOUND_HPP
#define __SOUND_HPP

#include <memory>
#include <string>

namespace SoLoud {
  class Soloud;
  class Wav;
}

namespace stemaj {

class Sound
{
public:
	static Sound& get();
	Sound(Sound const&) = delete;
	void operator=(Sound const&) = delete;

  void Play(const std::string& name, bool loop = true);
  void Stop(const float fadeTimeMs);
private:
  Sound();
  virtual ~Sound();
  
  bool _soundEnabled = false;

  bool _engineInitialized = false;
  std::string _currentlyPlaying = "";

  float _volume = 0.0f;

  unsigned int _handle;
  std::unique_ptr<SoLoud::Soloud> _soundEngine;
  std::unique_ptr<SoLoud::Wav> _sample;
};

#define SO Sound::get()

} // stemaj

#endif // __SOUND_HPP
