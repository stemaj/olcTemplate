#ifndef __DIALOG_HPP
#define __DIALOG_HPP

#include <olcTemplate/game/input.hpp>
#include <string>
#include <vector>

namespace stemaj
{

class Dialog
{
public:

  void Load(const std::string& name);

  void Update(const Input& input, float fElapsedTime);

  struct DialogNode
  {
    std::string speaker;
    std::string text;
    float duration;
    std::vector<std::pair<std::string, int>> options;
    int next = -1;
  };
  std::vector<DialogNode> dialogNodes;
  int currentNode = 0;
  float elapsedTime = 0.0f;
  bool displayingOptions = false;

  int _selection = -1;
};

} // namespace

#endif // __DIALOG_HPP