#ifndef __EXAMPLECOLLISIONRENDER_HPP
#define __EXAMPLECOLLISIONRENDER_HPP

#include <game/src/render/render.hpp>
#include <game/src/engine/olcPixelGameEngine.h>
#include <memory>

namespace stemaj {

class ExampleCollisionRender : public Render
{
public:
  explicit ExampleCollisionRender();
  void DoRender(olc::PixelGameEngine* pge, float fElapsedTime, State* state) override;

private:
  std::unique_ptr<olc::Renderable> _r;
};

} // namespace stemaj

#endif // __EXAMPLECOLLISIONRENDER_HPP
