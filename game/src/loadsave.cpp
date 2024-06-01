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

void LoadSave::Init(const std::string& level)
{
  _luaDefault.open_libraries(sol::lib::base, sol::lib::io, sol::lib::math, sol::lib::table);
	try
	{
		_luaDefault.safe_script_file("scripts/"+level+".lua");
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
			std::ofstream("scripts/profile/"+std::to_string(Profile)+"/"+level+".lua");
		}
		_luaProfile.safe_script_file("scripts/profile/"+std::to_string(Profile)+"/"+level+".lua");
	}
	catch (const sol::error& e)
	{
		std::cout << std::string(e.what()) << std::endl;
	}

	_outFile = std::ofstream("scripts/profile/1/"+level+".lua");
	if (!_outFile)
  {
    std::cout << "Unable to open file for writing";
  }
}

float LoadSave::Float(const std::string& name)
{
  return _luaProfile[name].get_or(_luaDefault[name].get_or(0.0f));
}

int LoadSave::Int(const std::string& name)
{
  return _luaProfile[name].get_or(_luaDefault[name].get_or(0));
}

PT<float> LoadSave::PTFloat(const std::string& name)
{
  auto f = PT<float>{0.0f,0.0f};
  auto arr = _luaProfile[name].get_or(_luaDefault[name].get_or(f));
  return { arr.x, arr.y };
}

std::array<PT<float>,4> LoadSave::PTFloat4(const std::string& name)
{
  
  std::array<PT<float>,4> arr;
  auto vec = _luaProfile[name].get_or(_luaDefault[name].get_or(arr));
   for (int i = 0; i < 4; i++)
   {
     arr[i] = { vec[i].x, vec[i].y };
   }
  return arr;
}

void LoadSave::SaveEmpty()
{
  _outFile << "\n";
}

void LoadSave::SaveFloat(const std::string& name, const float value)
{
	_outFile << name << " = " << value << "\n";
}

void LoadSave::SaveInt(const std::string& name, const int value)
{
  _outFile << name << " = " << value << "\n";
}

void LoadSave::SavePTFloat(const std::string& name, const PT<float>& value)
{
  _outFile << name << " = { " << value.x << ", " << value.y << " }\n";
}

void LoadSave::SavePTFloat4(const std::string& name, const std::array<PT<float>,4>& value)
{
  _outFile << name << " = { { " << value[0].x << ", " << value[0].y << "}, " << value[1].x << ", " << value[1].y << "}, " << value[2].x << ", " << value[2].y << "}, " << value[3].x << ", " << value[3].y << "} }";
}

void LoadSave::End()
{
	_outFile.close();
}
