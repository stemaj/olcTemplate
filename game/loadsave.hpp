#ifndef __LOADSAVE_HPP
#define __LOADSAVE_HPP

#include <string>
#define SOL_ALL_SAFETIES_ON 1
#include <olcTemplate/sdk/sol2-3.3.0/sol.hpp>
#include <fstream>
#include <olcTemplate/game/coordinates.hpp>

namespace stemaj {

class LoadSave
{
public:
	static LoadSave& get();
	LoadSave(LoadSave const&) = delete;
	void operator=(LoadSave const&) = delete;

	void Init(const std::string& level);
  
	float Float(const std::string& name);
	int Int(const std::string& name);
	bool Boolean(const std::string& name);
	PT<float> PTFloat(const std::string& name);
	PT<int> PTInt(const std::string& name);
  std::array<PT<float>,4> PTFloat4(const std::string& name);

	void SaveEmpty();
  void SaveFloat(const std::string& name, const float value);
  void SaveInt(const std::string& name, const int value);
	void SavePTInt(const std::string& name, const PT<int>& value);
  void SavePTFloat(const std::string& name, const PT<float>& value);
  void SavePTFloat4(const std::string& name, const std::array<PT<float>,4>& value);

  void SaveStart(const std::string& level);
	void SaveEnd();

	int Profile = 1;
private:
	std::ofstream _outFile;
  sol::state _luaProfile;
	sol::state _luaDefault;

  LoadSave() = default;
  virtual ~LoadSave();
};

#define LS LoadSave::get()

} // stemaj

#endif // __LOADSAVE_HPP
