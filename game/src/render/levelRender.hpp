#ifndef __LEVELRENDER_HPP
#define __LEVELRENDER_HPP

#include <game/src/render/render.hpp>

namespace stemaj {

class LevelRender : public Render
{
public:
  void DoRender(olc::PixelGameEngine* pge, float fElapsedTime, State* state) override;

protected:
  void Fade(olc::PixelGameEngine* pge, float fElapsedTime);
};

} // namespace stemaj

#endif //__LEVELRENDER_HPP