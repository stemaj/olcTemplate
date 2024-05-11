#ifndef __EXAMPLECOLLISIONRENDER_HPP
#define __EXAMPLECOLLISIONRENDER_HPP

#include <game/src/render/render.hpp>

namespace stemaj {

class ExampleCollisionRender : public Render
{
public:
  void DoRender(olc::PixelGameEngine* pge, float fElapsedTime, State* state) override;
};

} // namespace stemaj

#endif // __EXAMPLECOLLISIONRENDER_HPP