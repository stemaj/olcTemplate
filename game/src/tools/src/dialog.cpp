#include <olcTemplate/game/src/tools/dialog.hpp>
#define SOL_ALL_SAFETIES_ON 1
#include <olcTemplate/sdk/sol2-3.3.0/sol.hpp>

using namespace stemaj;

void Dialog::Load(const std::string& name)
{
  sol::state lua;
  lua.open_libraries(sol::lib::base, sol::lib::io, sol::lib::math, sol::lib::table);
	try
	{
		lua.safe_script_file("scripts/" + name + ".lua");
	}
	catch (const sol::error& e)
	{
		std::cout << std::string(e.what()) << std::endl;
	}

  sol::table dialog = lua["dialog"];
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
    dialogNodes.push_back(dialogNode);
  }
}

void Dialog::Update(const Input& input, float fElapsedTime)
{
  if (currentNode < dialogNodes.size())
  {
    elapsedTime += fElapsedTime;

    DialogNode &node = dialogNodes[currentNode];

    if (!displayingOptions && elapsedTime > node.duration) {
        if (!node.options.empty()) {
            displayingOptions = true;
        } else {
            currentNode = node.next;
            elapsedTime = 0.0f;
        }
    }

    if (displayingOptions && input.leftMouseClicked) {
        currentNode = node.options[0].second;
        displayingOptions = false;
        elapsedTime = 0.0f;
    }
    if (displayingOptions && input.spacePressed) {
        currentNode = node.options[1].second;
        displayingOptions = false;
        elapsedTime = 0.0f;
    }
  } 
}
