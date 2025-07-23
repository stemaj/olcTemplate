#ifndef __LOADSAVE_HPP
#define __LOADSAVE_HPP

#include "olcTemplate/game/guiElements.hpp"
#include "olcTemplate/game/input.hpp"
#include "olcTemplate/game/src/tools/dialog.hpp"
#include <string>
#include <unordered_map>
#include <vector>
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

	void Init(const std::string& luaFilePath, bool tryProfile);
  
	std::string String(const std::string& name, const std::string& defaultValue = "");
	float Float(const std::string& name, const float defaultValue = 0.0f);
	int Int(const std::string& name, const int defaultValue = 0);
	bool Boolean(const std::string& name);
	PT<float> PTFloat(const std::string& name);
	PT<int> PTInt(const std::string& name);
  std::array<PT<float>,4> PTFloat4(const std::string& name);
	std::vector<PT<float>> VPTFloat(const std::string& name);

	template<typename T1,typename T2>
	std::unordered_map<T1, T2> Map(const std::string& name)
	{
	  return _luaDefault[name].get_or(std::unordered_map<T1, T2>{});
	}

	std::vector<std::string> VString(const std::string& name);

	std::vector<Dialog::DialogNode> DialogNodes();

	std::unordered_map<ButtonAction, MainMenuGraphic> ButtonGraphics();
	std::unordered_map<ButtonAction, MainMenuText> ButtonTexts();
	std::vector<MainMenuColor> Colors();
	std::vector<MainMenuText> Texts();
	std::vector<MainMenuGraphic> Graphics();
	std::vector<IntroText> IntroTexts();
	std::vector<IntroGraphic> IntroGraphics();

	void SaveEmpty();
	void SaveString(const std::string& name, const std::string& value);
  void SaveFloat(const std::string& name, const float value);
  void SaveInt(const std::string& name, const int value);
	void SavePTInt(const std::string& name, const PT<int>& value);
  void SavePTFloat(const std::string& name, const PT<float>& value);
  void SavePTFloat4(const std::string& name, const std::array<PT<float>,4>& value);

  void SaveStart(const std::string& level);
	void SaveEnd();

	int Profile = 1;
protected:
	std::ofstream _outFile;
  sol::state _luaProfile;
	sol::state _luaDefault;

  LoadSave() = default;
  virtual ~LoadSave();
};

#define LS LoadSave::get()

} // stemaj

#endif // __LOADSAVE_HPP
