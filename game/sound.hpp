#ifndef __SOUND_HPP
#define __SOUND_HPP

#include <memory>
#include <string>
#include <vector>

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

  void StartMusic(const std::string& filePath, float volume, float fadeInTime = 0.0f);
  void StopMusic(float fadeOutTime = 0.0f);
  void StartEffect(const std::string& filepath, float volume);
  void StopAllEffects();
private:
  Sound();
  virtual ~Sound();
  
  bool _soundEnabled = false;

  unsigned int _musicHandle;
  std::unique_ptr<SoLoud::Soloud> _soundEngine;
  std::unique_ptr<SoLoud::Wav> _music;
  std::vector<std::unique_ptr<SoLoud::Wav>> _effects;
};

#define SO Sound::get()

} // stemaj

#endif // __SOUND_HPP
