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

void LoadSave::Init(const std::string& luaFilePath, bool tryProfile)
{
  _luaDefault.open_libraries(sol::lib::base, sol::lib::io, sol::lib::math, sol::lib::table);
	try
	{
		_luaDefault.safe_script_file(luaFilePath);
	}
	catch (const sol::error& e)
	{
		std::cout << std::string(e.what()) << std::endl;
	}

  if (tryProfile)
  {
    // _luaProfile.open_libraries(sol::lib::base, sol::lib::io, sol::lib::math, sol::lib::table);
    // try
    // {
    //   fs::path dir = "scripts/profile/"+std::to_string(Profile);
    //   if (!fs::exists(dir))
    //   {
    //     if (!fs::create_directories(dir))
    //     {
    //       std::cout << "failed to create profile directory\n";
    //     }
    //     std::ofstream("scripts/profile/"+std::to_string(Profile)+"/"+level+".lua");
    //   }
    //   _luaProfile.safe_script_file(
    //     "scripts/profile/"+std::to_string(Profile)+"/"+level+".lua");
    // }
    // catch (const sol::error& e)
    // {
    //   //std::cout << std::string(e.what()) << std::endl;
    // }
  }
}

std::string LoadSave::String(const std::string& name, const std::string& defaultValue)
{
  return _luaProfile[name].get_or(_luaDefault[name].get_or(defaultValue));
}

float LoadSave::Float(const std::string& name, const float defaultValue)
{
  return _luaProfile[name].get_or(_luaDefault[name].get_or(defaultValue));
}

int LoadSave::Int(const std::string& name, const int defaultValue)
{
  return _luaProfile[name].get_or(_luaDefault[name].get_or(defaultValue));
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
  auto d = _luaDefault[name].get_or<
    std::array<std::array<float,2>,4>>(f);
  auto vec = _luaProfile[name].get_or<
    std::array<std::array<float,2>,4>>(d);
  std::array<PT<float>,4> arr;
  for (int i = 0; i < 4; i++)
   {
     arr[i] = { PT<float>{vec[i][0], vec[i][1]} };
   }
  return arr;
}

std::vector<PT<float>> LoadSave::VPTFloat(const std::string& name)
{
  std::vector<PT<float>> ret;  
  auto vec = _luaDefault[name].get<std::vector<std::array<float,2>>>();
  for (const auto& v : vec)
  {
    ret.push_back({v[0],v[1]});
  }
  return ret;  
}

std::vector<std::string> LoadSave::VString(const std::string& name)
{
  return _luaDefault["animations"].get_or<std::vector<std::string>>({});
}

std::vector<MainMenuGraphic> LoadSave::Graphics()
{
  std::vector<MainMenuGraphic> ret;
  sol::table graphicsTable = _luaDefault["graphics"].get_or(
    sol::table(_luaDefault,sol::create));
  for (size_t i = 1; i <= graphicsTable.size(); i++)
  {
    sol::table t = graphicsTable[i];
    auto p = t.get_or<std::array<float, 2>>(2,{});
    ret.push_back({
      t.get_or<std::string>(1,""),
      CO.D({p[0],p[1]}),
      t.get_or(3,0.0f) });
  }
  return ret;
}

std::vector<IntroGraphic> LoadSave::IntroGraphics()
{
  std::vector<IntroGraphic> ret;
  sol::table graphicsTable = _luaDefault["graphics"].get_or(
    sol::table(_luaDefault,sol::create));
  for (size_t i = 1; i <= graphicsTable.size(); i++)
  {
    sol::table t = graphicsTable[i];
    auto p = t.get<std::array<float,2>>(2);
    ret.push_back( {
      t.get<std::string>(1),
      CO.D({p[0],p[1]}),
      t.get<float>(3),
      t.get<float>(4),
      t.get<float>(5)});
  }
  return ret;
}

std::vector<MainMenuText> LoadSave::Texts()
{
  std::vector<MainMenuText> ret;
  sol::table textsTable = _luaDefault["texts"].get_or(
    sol::table(_luaDefault,sol::create));
  for (size_t i = 1; i <= textsTable.size(); i++)
  {
    sol::table t = textsTable[i];
    auto p = t.get<std::array<float, 2>>(2);
    ret.push_back({
      t.get<std::string>(1),
      CO.D({p[0],p[1]}),
      (FontSize)t.get<int>(3),
      t.get<int>(4) });
  }
  return ret;
}

std::vector<IntroText> LoadSave::IntroTexts()
{
  std::vector<IntroText> ret;
  sol::table textsTable = _luaDefault["texts"].get_or(
    sol::table(_luaDefault,sol::create));
  for (size_t i = 1; i <= textsTable.size(); i++)
  {
    sol::table t = textsTable[i];
    auto p = t.get_or<std::array<float,2>>(2,{});
    ret.push_back( {
      t.get_or<std::string>(1,""),
      CO.D({p[0],p[1]}),
      (FontSize)t.get_or(3,0),
      t.get_or(4,0.0f),
      t.get_or(5,0.0f),
      t.get_or(6,0)});
  }
  return ret;
}

std::unordered_map<ButtonAction, MainMenuGraphic> LoadSave::ButtonGraphics()
{
  std::unordered_map<ButtonAction, MainMenuGraphic> ret;
  sol::table buttonsTable = _luaDefault["imageButtons"].get_or(
    sol::table(_luaDefault,sol::create));
  for (auto& [key, values] : buttonsTable)
  {
    auto p = ((sol::table)values).get_or<std::array<float, 2>>(2,{});
    ret[(ButtonAction)key.as<int>()] =
      {
        ((sol::table)values).get_or<std::string>(1,""),
        CO.D({p[0],p[1]}),
        1.0f,
        ((sol::table)values).get_or(3,0)
      };
  }
  return ret;
}

std::unordered_map<ButtonAction, MainMenuText> LoadSave::ButtonTexts()
{
  std::unordered_map<ButtonAction, MainMenuText> ret;
  sol::table buttonsTable = _luaDefault["buttons"].get_or(
    sol::table(_luaDefault,sol::create));
  for (auto& [key, values] : buttonsTable)
  {
    //int key = pair.first.as<int>();
    //sol::table values = pair.second;
    auto p = ((sol::table)values).get_or<std::array<float, 2>>(2,{});
    ret[(ButtonAction)key.as<int>()] = {
      ((sol::table)values).get_or<std::string>(1,""),
      CO.D({p[0],p[1]}),
      ((sol::table)values).get_or(3,(FontSize)0),
      ((sol::table)values).get_or(4,0),
      ((sol::table)values).get_or(5,0),
    };
  }
  return ret;  
}

std::vector<MainMenuColor> LoadSave::Colors()
{
  return _luaDefault["colors"].get_or<std::vector<MainMenuColor>>(
    {std::array<uint8_t, 4>({255,255,255,255})});
}

std::vector<Dialog::DialogNode> LoadSave::DialogNodes()
{
  std::vector<Dialog::DialogNode> ret;
  sol::table dialog = _luaDefault["dialog"];
  for (size_t i = 1; i <= dialog.size(); i++)
  {
    sol::table node = dialog[i];
    Dialog::DialogNode dialogNode;
    dialogNode.speaker = node["speaker"];
    dialogNode.text = node["text"];
    dialogNode.duration = node["duration"];
    if (node["next"].valid()) {
        dialogNode.next = node["next"];
    }

    if (node["options"].valid()) {
        sol::table options = node["options"];
        for (size_t j = 1; j <= options.size(); ++j) {
            sol::table option = options[j];
            dialogNode.options.emplace_back(option["text"], option["next"]);
        }
    }
    ret.push_back(dialogNode);
  }
  return ret;
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
  _outFile << name << " = { { " << value[0].x << ", " << value[0].y << " }, { "
    << value[1].x << ", " << value[1].y << " }, { " << value[2].x << ", " << value[2].y
    << " }, { " << value[3].x << ", " << value[3].y << " } }";
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
