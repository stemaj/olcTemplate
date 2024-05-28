#include <game/loadsave.hpp>
#include <string>

using namespace stemaj;

LoadSave& LoadSave::get()
{
  static LoadSave me;
  return me;
}

LoadSave::~LoadSave()
{
}

void LoadSave::Init(const std::string& name)
{
  _luaDefault.open_libraries(sol::lib::base, sol::lib::io, sol::lib::math, sol::lib::table);
	try
	{
		_luaDefault.safe_script_file("scripts/exampleCollision.lua");
	}
	catch (const sol::error& e)
	{
		std::cout << std::string(e.what()) << std::endl;
	}

  _luaProfile.open_libraries(sol::lib::base, sol::lib::io, sol::lib::math, sol::lib::table);
	try
	{
		_luaDefault.safe_script_file("scripts/profile/"+std::to_string(Profile)+"/exampleCollision.lua");
	}
	catch (const sol::error& e)
	{
		// thats ok
	}
}

float LoadSave::Float(const std::string& name)
{
  return _luaProfile[name].get_or(_luaDefault[name].get_or(0.0f));
}
