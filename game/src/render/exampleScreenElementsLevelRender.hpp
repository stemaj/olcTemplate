#ifndef __EXAMPLESCREENELEMENTSLEVELRENDER_HPP
#define __EXAMPLESCREENELEMENTSLEVELRENDER_HPP

#include <game/src/render/levelRender.hpp>

namespace stemaj {

class ExampleScreenElementsLevelRenderImpl;

class ExampleScreenElementsLevelRender : public LevelRender
{
public:
  ExampleScreenElementsLevelRender();
  virtual ~ExampleScreenElementsLevelRender();
  void DoRender(olc::PixelGameEngine* pge, float fElapsedTime, State* state) override;
private:
  ExampleScreenElementsLevelRenderImpl* _impl;
};

} // namespace stemaj

#endif // __EXAMPLESCREENELEMENTSLEVELRENDER_HPP