#include "b2_body.h"
#include <game/src/state/exampleCollisionState.hpp>
#include <game/src/render/exampleCollisionRender.hpp>
#include <game/src/render/levelRender.hpp>
#include <game/coordinates.hpp>

#include <sdk/box2d/include/box2d.h>

using namespace stemaj;

ExampleCollisionState::ExampleCollisionState() : _render(std::make_unique<ExampleCollisionRender>())
{
  LoadLevelData();
  InitValues();


  
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
  
  thingDef->type = b2_staticBody;
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

  _lua.open_libraries(sol::lib::base, sol::lib::io, sol::lib::math, sol::lib::table);
	try
	{
		_lua.safe_script_file("scripts/exampleCollision.lua");
	}
	catch (const sol::error& e)
	{
		std::cout << std::string(e.what()) << std::endl;
	}

  SCALE = _lua["scale"].get<float>();
  _gravityY = _lua["gravity_y"].get<float>();

  std::array<float,2> arr = _lua["ground_center"].get<std::array<float,2>>();
  _groundCenter = { int(arr[0]), int(arr[1]) };
  arr = _lua["ground_size"].get<std::array<float,2>>();
  _groundSize = { int(arr[0]), int(arr[1]) };
  _groundAngle = _lua["ground_angle"].get<float>();
}

void ExampleCollisionState::SaveLevelData()
{
  std::cout << "saving" << std::endl;
}

void ExampleCollisionState::InitValues()
{
  // Box2D World setup
  b2Vec2 gravity(0.0f, _gravityY);
  _world = std::make_unique<b2World>(gravity);

  b2BodyDef groundBodyDef;
  groundBodyDef.position.Set(_groundCenter.x, _groundCenter.y);
  groundBodyDef.angle = _groundAngle;
  b2Body* groundBody = _world->CreateBody(&groundBodyDef);
  b2PolygonShape groundBox;
  groundBox.SetAsBox(_groundSize.x, _groundSize.y);
  groundBody->CreateFixture(&groundBox, 1.0f);
}
