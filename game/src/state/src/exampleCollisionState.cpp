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
          groundBodyDef.position.Set(CO.W / 2.0f / SCALE, CO.H / SCALE);
          b2Body* groundBody = _world->CreateBody(&groundBodyDef);
          b2PolygonShape groundBox;
          groundBox.SetAsBox(CO.W / 2.0f / SCALE, 0.01f);
          groundBody->CreateFixture(&groundBox, 0.0f);
  
  
  // Create circle body (dynamic)
          b2BodyDef circleBodyDef;
          circleBodyDef.type = b2_dynamicBody;
          circleBodyDef.position.Set(CO.W / 2.0f / SCALE, 10.0f / SCALE);
          b2Body* circleBody = _world->CreateBody(&circleBodyDef);
          b2CircleShape circleShape;
          circleShape.m_radius = 20.0f / SCALE;
          circleBody->CreateFixture(&circleShape, 1.0f);
  
  // Create rectangle body (dynamic)
          b2BodyDef rectBodyDef;
          rectBodyDef.type = b2_dynamicBody;
          rectBodyDef.position.Set(CO.W / 2.0f / SCALE, 100.0f / SCALE);
          b2Body* rectBody = _world->CreateBody(&rectBodyDef);
          b2PolygonShape rectShape;
          rectShape.SetAsBox(30.0f / SCALE, 30.0f / SCALE);
          rectBody->CreateFixture(&rectShape, 1.0f);
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
