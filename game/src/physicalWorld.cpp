#include <olcTemplate/game/physicalWorld.hpp>
#include <olcTemplate/game/coordinates.hpp>
#include <olcTemplate/game/loadsave.hpp>
#define SOL_ALL_SAFETIES_ON 1
#include <olcTemplate/sdk/sol2-3.3.0/sol.hpp>

using namespace stemaj;

PhysicalWorld::~PhysicalWorld()
{
	if (_world == nullptr) return;
	
	for (auto& b : _bodyPtrs)
	{
		_world->DestroyBody(b.second);
		b.second = nullptr;
	}
	
	_bodyPtrs.clear();
	_world.reset();
	_world = nullptr;
}

void PhysicalWorld::LoadFromScript(const std::string& name, const std::string& prefix)
{
	//LS.Init(name);
	
	
	
	
	sol::state lua;
	lua.open_libraries(sol::lib::base, sol::lib::io, sol::lib::math, sol::lib::table);

	try
	{
		lua.safe_script_file("scripts/" + name + ".lua");
	}
	catch (const sol::error& e)
	{
		std::cout << std::string(e.what()) << std::endl;
	}
	
	_box2dScale = lua["box2d_scale"].get<float>();
	
	auto gravity = lua["box2d_gravity"].get<std::array<float,2>>();
	
	_world = std::make_unique<b2World>(b2Vec2(gravity[0], gravity[1]));
	
	sol::table rectsTable = lua[prefix + "_rects"];
	for (size_t i = 1; i <= rectsTable.size(); i++)
	{
		sol::table t = rectsTable[i];
		int id = t.get<int>(1);
		auto pos = t.get<std::array<float,2>>(2);
		auto size = t.get<std::array<float,2>>(3);
		auto angle = t.get<float>(4);
		auto type = t.get<int>(5);
		auto dens = t.get<float>(6);
		auto rest = t.get<float>(7);
		auto fric = t.get<float>(8);
		auto lDamp = t.get<float>(9);
		auto aDamp = t.get<float>(10);		

		b2PolygonShape polygonShape;
		polygonShape.SetAsBox(size[0]*_box2dScale,size[1]*_box2dScale);
		
		b2FixtureDef fixtureDef;
		fixtureDef.density = dens;
		fixtureDef.restitution = rest;
		fixtureDef.friction = fric;
		fixtureDef.shape = &polygonShape;

		b2BodyDef bodyDef;
		bodyDef.position.Set(pos[0]*_box2dScale,pos[1]*_box2dScale);
		bodyDef.type = (b2BodyType)type;
		bodyDef.angle = angle;
		_bodyPtrs[id] = _world->CreateBody(&bodyDef);
		_bodyPtrs[id]->CreateFixture(&fixtureDef);
		_bodyPtrs[id]->SetLinearDamping(lDamp);
		_bodyPtrs[id]->SetAngularDamping(aDamp);
		_bodyPtrs[id]->GetUserData().pointer = (uintptr_t)id;
	}
}

void PhysicalWorld::Step(float fElapsedTime)
{
	_world->Step(fElapsedTime, 6, 2);
}

PT<float> PhysicalWorld::GetCenterPoint(const int id)
{
	auto wc = _bodyPtrs[id]->GetWorldCenter();
	return { wc.x/_box2dScale, wc.y/_box2dScale };
}

void PhysicalWorld::SetBoostX(const int id, const float forceX, const float maxSpeedX)
{
	b2Body* body = _bodyPtrs[id];
	b2Vec2 velocity = body->GetLinearVelocity();
	if (velocity.x < maxSpeedX)
	{
		b2Vec2 force(forceX, 0.0f);
		b2Vec2 point = body->GetWorldCenter();
		body->ApplyForce(force, point, true);
	}
}

float PhysicalWorld::GetSpeedX(const int id)
{
	if (_bodyPtrs.contains(id))
		return _bodyPtrs[id]->GetLinearVelocity().x;
	return 0.0f;
}

std::unordered_map<int, std::vector<PT<float>>> PhysicalWorld::GetPolygons()
{
	std::unordered_map<int, std::vector<PT<float>>> ret;
	for (const auto& [id,body] : _bodyPtrs)
	{
		for (b2Fixture* fixture = body->GetFixtureList(); fixture; fixture = fixture->GetNext())
		{
			b2Shape* shape = fixture->GetShape();
			if (shape->GetType() == b2Shape::e_polygon)
			{
				ret[id] = GetPolygonVertex(id);
			}
		}
	}
	return ret;
}

std::unordered_map<int, std::pair<PT<float>,float>> PhysicalWorld::GetCircles()
{
	std::unordered_map<int, std::pair<PT<float>,float>> ret;
	for (const auto& [id,body] : _bodyPtrs)
	{
		for (b2Fixture* fixture = body->GetFixtureList(); fixture; fixture = fixture->GetNext())
		{
			b2Shape* shape = fixture->GetShape();
			if (shape->GetType() == b2Shape::e_circle)
			{
				ret[id] = GetCirclePosAndRadius(id);
			}
		}
	}
	return ret;
}

std::unordered_map<int, std::pair<PT<float>,PT<float>>> PhysicalWorld::GetEdges()
{
	std::unordered_map<int, std::pair<PT<float>,PT<float>>> ret;
	for (const auto& [id,body] : _bodyPtrs)
	{
		for (b2Fixture* fixture = body->GetFixtureList(); fixture; fixture = fixture->GetNext())
		{
			b2Shape* shape = fixture->GetShape();
			if (shape->GetType() == b2Shape::e_edge)
			{
				ret[id] = GetEdgeEndpoints(id);
			}
		}
	}
	return ret;
}

std::unordered_map<int, std::vector<PT<float>>> PhysicalWorld::GetChains()
{
	std::unordered_map<int, std::vector<PT<float>>> ret;
	for (const auto& [id,body] : _bodyPtrs)
	{
		for (b2Fixture* fixture = body->GetFixtureList(); fixture; fixture = fixture->GetNext())
		{
			b2Shape* shape = fixture->GetShape();
			if (shape->GetType() == b2Shape::e_chain)
			{
				ret[id] = GetChainVertex(id);
			}
		}
	}
	return ret;
}

std::vector<PT<float>> PhysicalWorld::GetPolygonVertex(const int id)
{
	std::vector<PT<float>> ret;
	auto body = _bodyPtrs[id];
	for (b2Fixture* fixture = body->GetFixtureList(); fixture; fixture = fixture->GetNext())
	{
		b2Shape* shape = fixture->GetShape();
		if (shape->GetType() != b2Shape::e_polygon) return {};
		
		b2PolygonShape* polygonShape = static_cast<b2PolygonShape*>(shape);
		int32 vertexCount = polygonShape->m_count;
		for (int i = 0; i < vertexCount; ++i)
		{
			b2Vec2 vertex = polygonShape->m_vertices[i];
			b2Vec2 worldVertex = body->GetWorldPoint(vertex);
			
			ret.emplace_back(PT<float>{worldVertex.x/_box2dScale, worldVertex.y/_box2dScale});
		}
	}
	return ret;
}

std::pair<PT<float>,float> PhysicalWorld::GetCirclePosAndRadius(const int id)
{
	std::pair<PT<float>,float> ret;
	auto body = _bodyPtrs[id];
	for (b2Fixture* fixture = body->GetFixtureList(); fixture; fixture = fixture->GetNext())
	{
		b2Shape* shape = fixture->GetShape();
		if (shape->GetType() != b2Shape::e_circle) return {};
		
		b2CircleShape* circleShape = static_cast<b2CircleShape*>(shape);
		b2Vec2 center = body->GetWorldPoint(circleShape->m_p);
		float radius = circleShape->m_radius;
		
		return {{center.x/_box2dScale,center.y/_box2dScale}, radius/_box2dScale};

//		// Optional: Berechnen von Punkten am Rand des Kreises
//		int numPoints = 20; // Anzahl der Punkte zur Darstellung des Kreises
//		for (int i = 0; i < numPoints; ++i) {
//				float angle = 2.0f * b2_pi * (float)i / (float)numPoints;
//				b2Vec2 point = center + radius * b2Vec2(cosf(angle), sinf(angle));
//				std::cout << "Circle Edge Point " << i << ": (" << point.x << ", " << point.y << ")" << std::endl;
//		}
	}
	return ret;
}

std::pair<PT<float>,PT<float>> PhysicalWorld::GetEdgeEndpoints(const int id)
{
	std::pair<PT<float>,PT<float>> ret;
	
	auto body = _bodyPtrs[id];
	for (b2Fixture* fixture = body->GetFixtureList(); fixture; fixture = fixture->GetNext())
	{
		b2Shape* shape = fixture->GetShape();
		if (shape->GetType() != b2Shape::e_edge) return {};
		
		b2EdgeShape* edgeShape = static_cast<b2EdgeShape*>(shape);
		b2Vec2 v1 = body->GetWorldPoint(edgeShape->m_vertex1);
		b2Vec2 v2 = body->GetWorldPoint(edgeShape->m_vertex2);
		return {{v1.x/_box2dScale,v1.y/_box2dScale},{v2.x/_box2dScale,v2.y/_box2dScale}};
	}
	return ret;
}

std::vector<PT<float>> PhysicalWorld::GetChainVertex(const int id)
{
	std::vector<PT<float>> ret;

	auto body = _bodyPtrs[id];
	for (b2Fixture* fixture = body->GetFixtureList(); fixture; fixture = fixture->GetNext())
	{
		b2Shape* shape = fixture->GetShape();
		if (shape->GetType() != b2Shape::e_chain) return {};
		
		b2ChainShape* chainShape = static_cast<b2ChainShape*>(shape);
		for (int i = 0; i < chainShape->m_count; ++i)
		{
			b2Vec2 vertex = body->GetWorldPoint(chainShape->m_vertices[i]);
			ret.emplace_back(PT<float>{vertex.x/_box2dScale,vertex.y/_box2dScale});
		}
	}
	return ret;
}
