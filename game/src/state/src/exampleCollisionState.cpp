#include <game/src/state/exampleCollisionState.hpp>
#include <game/src/render/exampleCollisionRender.hpp>
#include <game/src/render/levelRender.hpp>
#include <game/coordinates.hpp>

#include <sdk/box2d/include/box2d.h>

using namespace stemaj;

ExampleCollisionState::ExampleCollisionState() : _render(std::make_unique<ExampleCollisionRender>())
{
  LoadLevelData();


  
  // Box2D World setup
  b2Vec2 gravity(0.0f, 9.8f);
  _world = std::make_unique<b2World>(gravity);
  
  
  // Create ground body (static)
          b2BodyDef groundBodyDef;
          groundBodyDef.position.Set(CO.W / 2.0f / SCALE, CO.H * 8.0f / 10.0f / SCALE);
  groundBodyDef.angle = -b2_pi / 12.0f;

          b2Body* groundBody = _world->CreateBody(&groundBodyDef);
          b2PolygonShape groundBox;
          groundBox.SetAsBox(CO.W / 4.0f / SCALE, CO.H / 20.0f / SCALE);
          groundBody->CreateFixture(&groundBox, 0.0f);
  
  
  // Create circle body (dynamic)
          b2BodyDef circleBodyDef;
          circleBodyDef.type = b2_dynamicBody;
          circleBodyDef.position.Set(CO.W / 3.0f / SCALE, 10.0f / SCALE);
          b2Body* circleBody = _world->CreateBody(&circleBodyDef);
          b2CircleShape circleShape;
          circleShape.m_radius = 20.0f / SCALE;
          circleBody->CreateFixture(&circleShape, 1.0f);
  
  // Create rectangle body (dynamic)
          b2BodyDef rectBodyDef;
          rectBodyDef.type = b2_dynamicBody;
          rectBodyDef.position.Set(CO.W * 3.0f / 5.0f / SCALE, 10.0f / SCALE);
  rectBodyDef.angle = b2_pi / 5.0f;
          b2Body* rectBody = _world->CreateBody(&rectBodyDef);
          b2PolygonShape rectShape;
          rectShape.SetAsBox(10.0f / SCALE, 40.0f / SCALE);
          rectBody->CreateFixture(&rectShape, 1.0f);
  
  thingDef = std::make_unique<b2BodyDef>();
  
  thingDef->type = b2_kinematicBody;
  thingDef->position.Set(CO.W *8.0f / 9.0f / SCALE, 20.0f / SCALE);
  
  thingBody = _world->CreateBody(thingDef.get());
  b2PolygonShape thingShape;
  b2Vec2 tri[3];
  tri[0].Set(-10.0f / SCALE, -10.0f / SCALE);
  tri[1].Set( 10.0f / SCALE, -10.0f / SCALE);
  tri[2].Set(  0.0f / SCALE, 10.0f / SCALE);
  thingShape.Set(tri,3);
  thingBody->CreateFixture(&thingShape, 1.0f);
  
}

ExampleCollisionState::~ExampleCollisionState()
{
  SaveLevelData();
}

std::optional<std::unique_ptr<State>> ExampleCollisionState::Update(
  const Input& input, float fElapsedTime)
{
  
  // Step the Box2D simulation
          _world->Step(fElapsedTime, 6, 2);
  
  b2Vec2 pos;
  pos.x =input.mouseX / SCALE;
  pos.y =input.mouseY / SCALE;

  thingBody->SetTransform(pos, 0.0f);
  
  return std::nullopt;
}

Render* ExampleCollisionState::GetRender()
{
  return _render.get();
}

void ExampleCollisionState::LoadLevelData()
{
  std::cout << "loading" << std::endl;
}

void ExampleCollisionState::SaveLevelData()
{
  std::cout << "saving" << std::endl;
}
