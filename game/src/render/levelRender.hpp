#ifndef __LEVELRENDER_HPP
#define __LEVELRENDER_HPP

#include <game/src/render/render.hpp>

namespace stemaj {

class LevelRender : public Render
{
public:
  void DoRender(olc::PixelGameEngine* pge, float fElapsedTime, State* state) override;
};

} // namespace stemaj

#endif //__LEVELRENDER_HPP