#include <olcTemplate/game/src/tools/dialog.hpp>
#include <olcTemplate/game/loadsave.hpp>

using namespace stemaj;

void Dialog::Load(const std::string& name)
{
  LS.Init(name, false);
  dialogNodes = LS.DialogNodes();
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

    if (displayingOptions && input.leftMouseClicked && _selection == 0) {
        currentNode = node.options[0].second;
        displayingOptions = false;
        elapsedTime = 0.0f;
    }
    if (displayingOptions && input.leftMouseClicked && _selection == 1) {
        currentNode = node.options[1].second;
        displayingOptions = false;
        elapsedTime = 0.0f;
    }
    if (displayingOptions && input.leftMouseClicked && _selection == 2) {
        currentNode = node.options[2].second;
        displayingOptions = false;
        elapsedTime = 0.0f;
    }
  } 
}
