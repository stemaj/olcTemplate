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
#include <vector>

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
  _world->Step(fElapsedTime, _velocityIterations, _positionIterations);

  _triBodyPtr->SetTransform( b2Vec2(input.mouseX / SCALE, input.mouseY / SCALE) , 0.0f);

  b2Body* bodyListPtr = _world->GetBodyList();
  while (bodyListPtr != nullptr)
  {
    b2FixtureUserData data = bodyListPtr->GetFixtureList()->GetUserData();
    //auto i = reinterpret_cast<int>(data.pointer);


//    int shapeNr = std::reinterpret_reinterpret_cast<int>(bodyListPtr->GetFixtureList()->GetUserData());
    b2Shape::Type type = bodyListPtr->GetFixtureList()->GetType();
    if (type == b2Shape::Type::e_circle)
    {
      b2Vec2 circlePos = bodyListPtr->GetPosition();
      float circleRadius = ((b2CircleShape*)bodyListPtr->GetFixtureList()->GetShape())->m_radius * SCALE;
      
      // OlcHelper::FillCircleDecal(pge, circleRadius,circlePos.x * collisionLevel->SCALE, 
      // circlePos.y * collisionLevel->SCALE, olc::GREEN);
    }
    else if (type == b2Shape::Type::e_polygon)
    {
      b2PolygonShape* shape = (b2PolygonShape*)bodyListPtr->GetFixtureList()->GetShape();
      b2Vec2 vertices[shape->m_count];
      for (int i = 0; i < shape->m_count; i++)
      {
          vertices[i] = bodyListPtr->GetWorldPoint(shape->m_vertices[i]);
      }

    //   std::array<olc::vf2d,4> arr = {
    //       olc::vf2d{vertices[0].x * collisionLevel->SCALE, 
    //     vertices[0].y * collisionLevel->SCALE},
    //       olc::vf2d{vertices[1].x * collisionLevel->SCALE, 
    //     vertices[1].y * collisionLevel->SCALE},
    //       olc::vf2d{vertices[2].x * collisionLevel->SCALE, 
    //     vertices[2].y * collisionLevel->SCALE},
    //       olc::vf2d{vertices[3].x * collisionLevel->SCALE, 
    //     vertices[3].y * collisionLevel->SCALE}
      
    //   };

    //  pge->DrawWarpedDecal(
    //           _r->Decal(),
    //           arr,
    //           olc::YELLOW);
    }
  }
    
    bodyListPtr = bodyListPtr->GetNext();

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
    _triPolygon[i] = { vec[i][0], vec[i][1] };
  }
  _triType = _lua["tri_type"].get<int>();
  _triDensity = _lua["tri_density"].get<float>();
}

void ExampleCollisionState::SaveLevelData()
{
  std::cout << "saving" << std::endl;
}

struct Test
{

};

void ExampleCollisionState::InitValues()
{
  // Box2D World setup
  b2Vec2 gravity(0.0f, _gravityY);
  _world = std::make_unique<b2World>(gravity);

  b2BodyDef groundBodyDef;
  groundBodyDef.position.Set(_groundCenter.x, _groundCenter.y);
  groundBodyDef.type = (b2BodyType)_groundType;
  groundBodyDef.angle = _groundAngle;
  int* groundUserdata = new int(0);
  groundBodyDef.userData.pointer = reinterpret_cast<uintptr_t>(groundUserdata);
  b2Body* groundBody = _world->CreateBody(&groundBodyDef);
  b2PolygonShape groundBox;
  groundBox.SetAsBox(_groundSize.x, _groundSize.y);
  groundBody->CreateFixture(&groundBox, _groundDensity);

  b2BodyDef circleBodyDef;
  circleBodyDef.type = (b2BodyType)_circleType;
  circleBodyDef.position.Set(_circleCenter.x, _circleCenter.y);
  int* circleUserdata = new int(1);
  groundBodyDef.userData.pointer = reinterpret_cast<uintptr_t>(circleUserdata);
  b2Body* circleBody = _world->CreateBody(&circleBodyDef);
  b2CircleShape circleShape;
  circleShape.m_radius = _circleRadius;
  circleBody->CreateFixture(&circleShape, _circleDensity);

  b2BodyDef rectBodyDef;
  rectBodyDef.type = (b2BodyType)_rectType;
  rectBodyDef.position.Set(_rectCenter.x, _rectCenter.y);
  rectBodyDef.angle = _rectAngle;
  int* rectUserdata = new int(2);
  groundBodyDef.userData.pointer = reinterpret_cast<uintptr_t>(rectUserdata);
  b2Body* rectBody = _world->CreateBody(&rectBodyDef);
  b2PolygonShape rectShape;
  rectShape.SetAsBox(_rectSize.x, _rectSize.y);
  rectBody->CreateFixture(&rectShape, _rectDensity);

  b2BodyDef triBodyDef;
  triBodyDef.type = (b2BodyType)_triType;
  triBodyDef.position.Set(_triCenter.x, _triCenter.y);
  int* triUserData = new int(3);
  groundBodyDef.userData.pointer = reinterpret_cast<uintptr_t>(triUserData);
  _triBodyPtr = _world->CreateBody(&triBodyDef);
  b2PolygonShape triShape;
  b2Vec2 triVec[_triPolygon.size()];
  for (int i = 0; i < _triPolygon.size(); i++)
  {
    triVec[i].Set(_triPolygon[i].x, _triPolygon[i].y);
  }
  triShape.Set(triVec, _triPolygon.size());
  _triBodyPtr->CreateFixture(&triShape, _triDensity);
}
