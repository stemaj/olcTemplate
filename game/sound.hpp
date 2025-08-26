#ifndef __SOUND_HPP
#define __SOUND_HPP

#include <memory>
#include <string>
#include <unordered_map>

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
  void StopEffect(const std::string& filepath, float fadeOutTime = 0.0f);
  void StopAllEffects();
private:
  Sound();
  virtual ~Sound();
  std::unique_ptr<SoLoud::Soloud> _soundEngine;
  
  bool _soundEnabled = false;
  unsigned int _musicHandle;
  std::unique_ptr<SoLoud::Wav> _music;
  std::unordered_map<std::string, unsigned int> _effectHandles;
  std::unordered_map<std::string, std::unique_ptr<SoLoud::Wav>> _effects;
};

#define SO Sound::get()

} // stemaj

#endif // __SOUND_HPP
