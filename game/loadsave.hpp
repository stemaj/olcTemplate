#ifndef __LOADSAVE_HPP
#define __LOADSAVE_HPP

#include <string>
#define SOL_ALL_SAFETIES_ON 1
#include <olcTemplate/sdk/sol2-3.3.0/sol.hpp>
#include <fstream>

namespace stemaj {

class LoadSave
{
public:
	static LoadSave& get();
	LoadSave(LoadSave const&) = delete;
	void operator=(LoadSave const&) = delete;

	void Init(const std::string& name);
	float Float(const std::string& name);
	void SaveFloat(const std::string& name, const float value);
	
	void End();

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