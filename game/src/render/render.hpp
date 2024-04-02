#ifndef __RENDER_HPP
#define __RENDER_HPP

#include <memory>

namespace olc {
  class PixelGameEngine;
}

namespace stemaj {

class State;

class Render
{
public:
  virtual ~Render() = default;
  virtual void Update(olc::PixelGameEngine* pge, float fElapsedTime, std::unique_ptr<State>) = 0;
};

} // namespace stemaj

#endif //__RENDER_HPP