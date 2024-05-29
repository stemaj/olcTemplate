#include <olcTemplate/game/loadsave.hpp>
#include <string>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;
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
		_luaDefault.safe_script_file("scripts/"+name+".lua");
	}
	catch (const sol::error& e)
	{
		std::cout << std::string(e.what()) << std::endl;
	}

  _luaProfile.open_libraries(sol::lib::base, sol::lib::io, sol::lib::math, sol::lib::table);
	try
	{
		fs::path dir = "scripts/profile/"+std::to_string(Profile);
		if (!fs::exists(dir))
		{
			if (!fs::create_directories(dir))
			{
				std::cout << "failed to create profile directory\n";
			}
			std::ofstream("scripts/profile/"+std::to_string(Profile)+"/"+name+".lua");
		}
		_luaProfile.safe_script_file("scripts/profile/"+std::to_string(Profile)+"/"+name+".lua");
	}
	catch (const sol::error& e)
	{
		std::cout << std::string(e.what()) << std::endl;
	}

	_outFile = std::ofstream("scripts/profile/1/"+name+".lua");
	if (!_outFile)
  {
    std::cout << "Unable to open file for writing";
  }
}

float LoadSave::Float(const std::string& name)
{
  return _luaProfile[name].get_or(_luaDefault[name].get_or(0.0f));
}

void LoadSave::SaveFloat(const std::string& name, const float value)
{
	_outFile << name << " = " << value << "\n";
}

void LoadSave::End()
{
	_outFile.close();
}