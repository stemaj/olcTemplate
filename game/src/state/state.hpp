#ifndef __STATE_HPP
#define __STATE_HPP

#include <game/input.hpp>

namespace stemaj {

class Render;

class State
{
public:
  virtual ~State() = default;
  virtual void Update(const Input& input) = 0;
  virtual Render* GetRender() = 0;
};

} // namespace stemaj

#endif //__STATE_HPP