#ifndef __STATE_HPP
#define __STATE_HPP

#include <game/input.hpp>
#include <memory>
#include <optional>

namespace stemaj {

class Render;

class State
{
public:
  virtual ~State() = default;
  virtual std::optional<std::unique_ptr<State>> Update(const Input& input) = 0;
  virtual Render* GetRender() = 0;
};

} // namespace stemaj

#endif //__STATE_HPP