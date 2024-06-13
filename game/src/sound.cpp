#include <olcTemplate/game/sound.hpp>
#include <olcTemplate/sdk/soloud/include/soloud.h>
#include <olcTemplate/sdk/soloud/include/soloud_wav.h>
#define SOL_ALL_SAFETIES_ON 1
#include <olcTemplate/sdk/sol2-3.3.0/sol.hpp>

using namespace stemaj;

Sound& Sound::get()
{
  static Sound me;
  return me;
}

Sound::Sound()
{
  sol::state lua;
  lua.open_libraries(sol::lib::base, sol::lib::io, sol::lib::math, sol::lib::table);
  try
  {
    lua.safe_script_file("scripts/settings.lua");
  }
  catch (const sol::error& e)
  {
    std::cout << std::string(e.what()) << std::endl;
  }

  _soundEnabled = lua["sound"].get_or(false);
}

Sound::~Sound()
{
  if (_soundEnabled)
  {
    _soundEngine->deinit();
  }
}

void Sound::Play(const std::string& name)
{
  if (!_soundEnabled) return;

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

  std::cout << "playing sound\n";


  _currentlyPlaying = name;
}
