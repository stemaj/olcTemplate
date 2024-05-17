#include "b2_body.h"
#include "b2_math.h"
#include "b2_settings.h"
#include <array>
#include <game/src/state/exampleCollisionState.hpp>
#include <game/src/render/exampleCollisionRender.hpp>
#include <game/src/render/levelRender.hpp>
#include <game/coordinates.hpp>

#include <memory>
#include <sdk/box2d/include/box2d.h>

using namespace stemaj;

ExampleCollisionState::ExampleCollisionState() : _render(std::make_unique<ExampleCollisionRender>())
{
  LoadLevelData();
  InitValues();
}

ExampleCollisionState::~ExampleCollisionState()
{
  SaveLevelData();
}

std::optional<std::unique_ptr<State>> ExampleCollisionState::Update(
  const Input& input, float fElapsedTime)
{
  if (input.aHold) _force.x -= _triForce;
  else if (input.dHold) _force.x += _triForce;
  else _force.x = 0;

  if (input.wHold) _force.y -= _triForce;
  else if (input.sHold) _force.y += _triForce;
  else _force.y = 0;

  b2Body* bodyListPtr = _world->GetBodyList();
  while (bodyListPtr != nullptr)
  {
    auto fixtureList = bodyListPtr->GetFixtureList();
    b2PolygonShape* shape = (b2PolygonShape*)fixtureList->GetShape();
    uintptr_t pointer = fixtureList->GetUserData().pointer;
    Identifier* id = reinterpret_cast<Identifier*>(pointer);
    if (id == nullptr)
    {
      std::cout << "Fehler beim Holen der Id\n";
      std::exit(1);
    }
    if (id->id == 2)
    {
      b2Vec2 circlePos = bodyListPtr->GetPosition();
      _circleCenter = { circlePos.x, circlePos.y };
    }
    else
    {
      if (id->id == 1)
      {
        for (int i = 0; i < shape->m_count; i++)
        {
          auto vertex = bodyListPtr->GetWorldPoint(shape->m_vertices[i]);
          _groundShape[i] = { vertex.x, vertex.y };
        }
        _groundCenter = { bodyListPtr->GetPosition().x, bodyListPtr->GetPosition().y };
        _groundAngle = bodyListPtr->GetAngle();
      }
      else if (id->id == 3)
      {
        for (int i = 0; i < shape->m_count; i++)
        {
          auto vertex = bodyListPtr->GetWorldPoint(shape->m_vertices[i]);
          _rectShape[i] = { vertex.x, vertex.y };
        }
        _rectCenter = { bodyListPtr->GetPosition().x, bodyListPtr->GetPosition().y };
        _rectAngle = bodyListPtr->GetAngle();
      }
      else if (id->id == 4)
      {
        for (int i = 0; i < shape->m_count; i++)
        {
          auto vertex = bodyListPtr->GetWorldPoint(shape->m_vertices[i]);
          _triShape[i] = { vertex.x, vertex.y };
        }
        _triCenter = { bodyListPtr->GetPosition().x, bodyListPtr->GetPosition().y };
        b2Vec2 force = {_force.x * fElapsedTime,_force.y * fElapsedTime};
        force.Normalize();
        _triBodyPtr->ApplyForceToCenter(force, true);
        //_triBodyPtr->SetTransform( b2Vec2(input.mouseX / SCALE, input.mouseY / SCALE) , 0.0f);
      }
    }
    bodyListPtr = bodyListPtr->GetNext();
  }

  _world->Step(fElapsedTime, _velocityIterations, _positionIterations);
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

  _velocityIterations = _lua["velocity_iterations"].get<int>();
  _positionIterations = _lua["position_iterations"].get<int>();
  
  _gravityY = _lua["gravity_y"].get<float>();

  std::array<float,2> arr = _lua["ground_center"].get<std::array<float,2>>();
  _groundCenter = {arr[0], arr[1] };
  arr = _lua["ground_size"].get<std::array<float,2>>();
  _groundSize = { arr[0], arr[1] };
  _groundAngle = _lua["ground_angle"].get<float>();
  _groundType = _lua["ground_type"].get<int>();
  _groundDensity = _lua["ground_density"].get<float>();

  arr = _lua["circle_center"].get<std::array<float,2>>();
  _circleCenter = { arr[0], arr[1] };
  _circleRadius = _lua["circle_radius"].get<float>();
  _circleType = _lua["circle_type"].get<int>();
  _circleDensity = _lua["circle_density"].get<float>();

  arr = _lua["rect_center"].get<std::array<float,2>>();
  _rectCenter = { arr[0], arr[1] };
  arr = _lua["rect_size"].get<std::array<float,2>>();
  _rectSize = { arr[0], arr[1] };
  _rectAngle = _lua["rect_angle"].get<float>();
  _rectType = _lua["rect_type"].get<int>();
  _rectDensity = _lua["rect_density"].get<float>();

  arr = _lua["tri_center"].get<std::array<float,2>>();
  _triCenter = { arr[0], arr[1] };
  auto vec = _lua["tri_polygon"].get<std::array<std::array<float,2>,4>>();
  for (int i = 0; i < 4; i++)
  {
    _triShape[i] = { vec[i][0], vec[i][1] };
  }
  _triType = _lua["tri_type"].get<int>();
  _triDensity = _lua["tri_density"].get<float>();
  _triForce = _lua["tri_force"].get<float>();
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
  groundBodyDef.type = (b2BodyType)_groundType;
  groundBodyDef.angle = _groundAngle;
  groundBodyDef.userData.pointer = reinterpret_cast<uintptr_t>(&_idGround);
  b2Body* groundBody = _world->CreateBody(&groundBodyDef);
  b2PolygonShape groundBox;
  groundBox.SetAsBox(_groundSize.x, _groundSize.y);
  b2FixtureDef groundFixtureDef;
  groundFixtureDef.density = _groundDensity;
  groundFixtureDef.shape = &groundBox;
  groundFixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(&_idGround);
  groundBody->CreateFixture(&groundFixtureDef);

  b2BodyDef circleBodyDef;
  circleBodyDef.type = (b2BodyType)_circleType;
  circleBodyDef.position.Set(_circleCenter.x, _circleCenter.y);
  b2Body* circleBody = _world->CreateBody(&circleBodyDef);
  b2CircleShape circleShape;
  circleShape.m_radius = _circleRadius;
  b2FixtureDef circleFixtureDef;
  circleFixtureDef.density = _circleDensity;
  circleFixtureDef.shape = &circleShape;
  circleFixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(&_idCircle);
  circleBody->CreateFixture(&circleFixtureDef);

  b2BodyDef rectBodyDef;
  rectBodyDef.type = (b2BodyType)_rectType;
  rectBodyDef.position.Set(_rectCenter.x, _rectCenter.y);
  rectBodyDef.angle = _rectAngle;
  b2Body* rectBody = _world->CreateBody(&rectBodyDef);
  b2PolygonShape rectShape;
  rectShape.SetAsBox(_rectSize.x, _rectSize.y);
  b2FixtureDef rectFixtureDef;
  rectFixtureDef.density = _rectDensity;
  rectFixtureDef.shape = &rectShape;
  rectFixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(&_idRect);
  rectBody->CreateFixture(&rectFixtureDef);

  b2BodyDef triBodyDef;
  triBodyDef.type = (b2BodyType)_triType;
  triBodyDef.position.Set(_triCenter.x, _triCenter.y);
  _triBodyPtr = _world->CreateBody(&triBodyDef);
  b2PolygonShape triShape;
  b2Vec2 triVec[_triShape.size()];
  for (int i = 0; i < _triShape.size(); i++)
  {
    triVec[i].Set(_triShape[i].x, _triShape[i].y);
  }
  triShape.Set(triVec, _triShape.size());
  b2FixtureDef triFixtureDef;
  triFixtureDef.density = _triDensity;
  triFixtureDef.shape = &triShape;
  triFixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(&_idTri);
  _triBodyPtr->SetGravityScale(0);
  _triBodyPtr->CreateFixture(&triFixtureDef);
}
