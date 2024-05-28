#ifndef __LOADSAVE_HPP
#define __LOADSAVE_HPP

#include <string>
#define SOL_ALL_SAFETIES_ON 1
#include <sdk/sol2-3.3.0/sol.hpp>

namespace stemaj {

class LoadSave
{
public:
	static LoadSave& get();
	LoadSave(LoadSave const&) = delete;
	void operator=(LoadSave const&) = delete;

	void Init(const std::string& name);
	float Float(const std::string& name);

	int Profile = 1;
private:
  sol::state _luaProfile;
	sol::state _luaDefault;

  LoadSave() = default;
  virtual ~LoadSave();
};

#define LS LoadSave::get()

} // stemaj

#endif // __LOADSAVE_HPP