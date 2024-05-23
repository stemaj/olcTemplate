#ifndef __RENDER_HPP
#define __RENDER_HPP

namespace olc {
  class PixelGameEngine;
}

namespace stemaj {

class State;

class Render
{
public:
  virtual ~Render() = default;
  virtual void DoRender(olc::PixelGameEngine* pge, float fElapsedTime, State* state) = 0;
  virtual void Fade(olc::PixelGameEngine* pge, State* state) = 0;
};

} // namespace stemaj

#endif //__RENDER_HPP