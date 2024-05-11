#include <game/src/render/exampleCollisionRender.hpp>
#include <game/src/state/exampleCollisionState.hpp>
#include <game/src/engine/olcPixelGameEngine.h>
#include <string>

#include <sdk/box2d/include/box2d.h>

using namespace stemaj;

void ExampleCollisionRender::DoRender(olc::PixelGameEngine* pge, float fElapsedTime, State* state)
{
  auto collisionLevel = static_cast<ExampleCollisionState*>(state);
  
  // Clear screen
          pge->Clear(olc::BLACK);

  // Draw circle
     b2Body* circleBody = collisionLevel->_world->GetBodyList();
     while (circleBody)
     {
         b2Vec2 circlePos = circleBody->GetPosition();
         float circleRadius = ((b2CircleShape*)circleBody->GetFixtureList()->GetShape())->m_radius * collisionLevel->SCALE;
         pge->DrawCircle(circlePos.x * collisionLevel->SCALE, circlePos.y * collisionLevel->SCALE, circleRadius, olc::GREEN);
         circleBody = circleBody->GetNext();
     }
  
  // Draw rectangles
          b2Body* rectBody = collisionLevel->_world->GetBodyList();
          while (rectBody)
          {
              b2Vec2 rectPos = rectBody->GetPosition();
              b2PolygonShape* shape = (b2PolygonShape*)rectBody->GetFixtureList()->GetShape();
              b2Vec2 vertices[4];
              for (int i = 0; i < 4; i++)
              {
                  vertices[i] = rectBody->GetWorldPoint(shape->m_vertices[i]);
              }
              pge->DrawRect(vertices[0].x * collisionLevel->SCALE, vertices[0].y * collisionLevel->SCALE, (vertices[2].x - vertices[0].x) * collisionLevel->SCALE, (vertices[2].y - vertices[0].y) * collisionLevel->SCALE, olc::BLUE);
              rectBody = rectBody->GetNext();
          }
  
}
