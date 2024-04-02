#ifndef __STATE_HPP
#define __STATE_HPP

#include <memory>
#include <game/input.hpp>

namespace stemaj {

class Render;

class State
{
public:
  virtual ~State() = default;
  virtual std::unique_ptr<Render> Update(Input input) = 0;
};

} // namespace stemaj

#endif //__STATE_HPP