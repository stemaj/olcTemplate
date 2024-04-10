#ifndef __EXAMPLEPATHLEVELRENDER_HPP
#define __EXAMPLEPATHLEVELRENDER_HPP

#include <game/src/render/render.hpp>

namespace stemaj {

class ExamplePathLevelRender : public Render
{
public:
  void DoRender(olc::PixelGameEngine* pge, float fElapsedTime, State* state) override;
};

} // namespace stemaj

#endif // __EXAMPLEPATHLEVELRENDER_HPP