#include <game/src/render/exampleCollisionRender.hpp>
#include <game/src/state/exampleCollisionState.hpp>
#include <game/src/render/helper/olcHelper.hpp>

#include <memory>
#include <string>
#include <array>

#include <sdk/box2d/include/box2d.h>

using namespace stemaj;

ExampleCollisionRender::ExampleCollisionRender()
 : _r(std::make_unique<olc::Renderable>())
{
  OlcHelper::CreateOneColorDecal(_r.get(), olc::YELLOW);
}

void ExampleCollisionRender::DoRender(olc::PixelGameEngine* pge, float fElapsedTime, State* state)
{
  auto collisionLevel = static_cast<ExampleCollisionState*>(state);
  
  pge->Clear(olc::DARK_MAGENTA);
  
  b2Body* bodyListPtr = collisionLevel->_world->GetBodyList();
  while (bodyListPtr != nullptr)
  {
    b2Shape::Type type = bodyListPtr->GetFixtureList()->GetType();
    if (type == b2Shape::Type::e_circle)
    {
      b2Vec2 circlePos = bodyListPtr->GetPosition();
      float circleRadius = ((b2CircleShape*)bodyListPtr->GetFixtureList()->GetShape())->m_radius * collisionLevel->SCALE;
      
      OlcHelper::FillCircleDecal(pge, circleRadius,circlePos.x * collisionLevel->SCALE, 
      circlePos.y * collisionLevel->SCALE, olc::GREEN);
    }
    else if (type == b2Shape::Type::e_polygon)
    {
      b2PolygonShape* shape = (b2PolygonShape*)bodyListPtr->GetFixtureList()->GetShape();
      b2Vec2 vertices[4];
      for (int i = 0; i < 4; i++)
      {
          vertices[i] = bodyListPtr->GetWorldPoint(shape->m_vertices[i]);
      }

      std::array<olc::vf2d,4> arr = {
          olc::vf2d{vertices[0].x * collisionLevel->SCALE, 
        vertices[0].y * collisionLevel->SCALE},
          olc::vf2d{vertices[1].x * collisionLevel->SCALE, 
        vertices[1].y * collisionLevel->SCALE},
          olc::vf2d{vertices[2].x * collisionLevel->SCALE, 
        vertices[2].y * collisionLevel->SCALE},
          olc::vf2d{vertices[3].x * collisionLevel->SCALE, 
        vertices[3].y * collisionLevel->SCALE}
      
      };

     pge->DrawWarpedDecal(
              _r->Decal(),
              arr,
              olc::YELLOW);
    }
    
    
    bodyListPtr = bodyListPtr->GetNext();
    
  }
}
