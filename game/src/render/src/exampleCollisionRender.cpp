#include <game/src/render/exampleCollisionRender.hpp>
#include <game/src/state/exampleCollisionState.hpp>
#include <game/src/render/helper/olcHelper.hpp>

#include <memory>
#include <string>
#include <array>

#include <sdk/box2d/include/box2d.h>

using namespace stemaj;

ExampleCollisionRender::ExampleCollisionRender()
 : _rGround(std::make_unique<olc::Renderable>()),
   _rRect(std::make_unique<olc::Renderable>()),
   _rTri(std::make_unique<olc::Renderable>())
{
  OlcHelper::CreateOneColorDecal(_rGround.get(), olc::YELLOW);
  OlcHelper::CreateOneColorDecal(_rRect.get(), olc::BLUE);
  OlcHelper::CreateOneColorDecal(_rTri.get(), olc::RED);
}

void ExampleCollisionRender::DoRender(olc::PixelGameEngine* pge, float fElapsedTime, State* state)
{
  auto collisionLevel = static_cast<ExampleCollisionState*>(state);
  
  pge->Clear(olc::DARK_MAGENTA);

  std::array<olc::vf2d,4> arr;
  for (int i = 0; i < 4; i++)
  {
    arr[i] = { collisionLevel->_groundShape[i].x * collisionLevel->SCALE, 
               collisionLevel->_groundShape[i].y * collisionLevel->SCALE };
  }
  pge->DrawWarpedDecal(_rGround->Decal(), arr);

  OlcHelper::FillCircleDecal(pge,
    collisionLevel->_circleRadius *  collisionLevel->SCALE,
    { int(collisionLevel->_circleCenter.x * collisionLevel->SCALE),
      int(collisionLevel->_circleCenter.y * collisionLevel->SCALE) },
      olc::GREEN);

  for (int i = 0; i < 4; i++)
  {
    arr[i] = { collisionLevel->_rectShape[i].x * collisionLevel->SCALE, 
               collisionLevel->_rectShape[i].y * collisionLevel->SCALE };
  }
  pge->DrawWarpedDecal(_rRect->Decal(), arr);

  for (int i = 0; i < 4; i++)
  {
    arr[i] = { collisionLevel->_triShape[i].x * collisionLevel->SCALE, 
               collisionLevel->_triShape[i].y * collisionLevel->SCALE };
  }
  pge->DrawWarpedDecal(_rTri->Decal(), arr);
}
