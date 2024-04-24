#ifndef __EXAMPLESCREENELEMENTSLEVELRENDER_HPP
#define __EXAMPLESCREENELEMENTSLEVELRENDER_HPP

#include <game/src/render/render.hpp>

namespace stemaj {

class ExampleScreenElementsLevelRender : public Render
{
public:
  void DoRender(olc::PixelGameEngine* pge, float fElapsedTime, State* state) override;
};

} // namespace stemaj

#endif // __EXAMPLESCREENELEMENTSLEVELRENDER_HPP