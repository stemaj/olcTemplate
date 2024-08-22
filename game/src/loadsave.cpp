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
}

std::string LoadSave::String(const std::string& name)
{
  return _luaProfile[name].get_or(_luaDefault[name].get_or(std::string()));
}

float LoadSave::Float(const std::string& name)
{
  return _luaProfile[name].get_or(_luaDefault[name].get_or(0.0f));
}

int LoadSave::Int(const std::string& name)
{
  return _luaProfile[name].get_or(_luaDefault[name].get_or(0));
}

bool LoadSave::Boolean(const std::string& name)
{
  return _luaProfile[name].get_or(_luaDefault[name].get_or(false));
}

PT<float> LoadSave::PTFloat(const std::string& name)
{
  std::array<float,2> f = {};
  auto d = _luaDefault[name].get_or<std::array<float,2>>(f);
  auto arr = _luaProfile[name].get_or<std::array<float,2>>(d);
  return { arr[0], arr[1] };
}

PT<int> LoadSave::PTInt(const std::string& name)
{
  std::array<int,2> f = {};
  auto d = _luaDefault[name].get_or<std::array<int,2>>(f);
  auto arr = _luaProfile[name].get_or<std::array<int,2>>(d);
  return { arr[0], arr[1] };
}

std::array<PT<float>,4> LoadSave::PTFloat4(const std::string& name)
{
  std::array<std::array<float,2>,4> f = {};
  auto d = _luaDefault[name].get_or<std::array<std::array<float,2>,4>>(f);
  auto vec = _luaProfile[name].get_or<std::array<std::array<float,2>,4>>(d);
  std::array<PT<float>,4> arr;
  for (int i = 0; i < 4; i++)
   {
     arr[i] = { PT<float>{vec[i][0], vec[i][1]} };
   }
  return arr;
}

void LoadSave::SaveEmpty()
{
  _outFile << "\n";
}

void LoadSave::SaveString(const std::string& name, const std::string& value)
{
  _outFile << name << " = " << value << "\n";
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

void LoadSave::SavePTInt(const std::string& name, const PT<int>& value)
{
  _outFile << name << " = { " << value.x << ", " << value.y << " }\n";
}

void LoadSave::SavePTFloat4(const std::string& name, const std::array<PT<float>,4>& value)
{
  _outFile << name << " = { { " << value[0].x << ", " << value[0].y << " }, { " << value[1].x << ", " << value[1].y << " }, { " << value[2].x << ", " << value[2].y << " }, { " << value[3].x << ", " << value[3].y << " } }";
}

void LoadSave::SaveStart(const std::string& level)
{
  _outFile = std::ofstream("scripts/profile/1/"+level+".lua");
  if (!_outFile)
  {
    std::cout << "Unable to open file for writing";
  }
}

void LoadSave::SaveEnd()
{
	_outFile.close();
}
