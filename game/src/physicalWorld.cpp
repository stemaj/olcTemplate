#include <olcTemplate/game/physicalWorld.hpp>
#include <olcTemplate/game/coordinates.hpp>
#include <olcTemplate/game/loadsave.hpp>
#define SOL_ALL_SAFETIES_ON 1
#include <olcTemplate/sdk/sol2-3.3.0/sol.hpp>
#include <algorithm>

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

void PhysicalWorld::LoadFromScript(const std::string& name,
	const std::string& prefix, std::list<int>& userdata)
{
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
	
	_box2dScale = lua["box2d_scale"].get_or(0.0f);
	
	auto gravity = lua["box2d_gravity"].get_or<std::array<float,2>>({});
	
	_world = std::make_unique<b2World>(b2Vec2(gravity[0], gravity[1]));
	
	sol::table rectsTable = lua[prefix + "_rects"].get_or(sol::table());
	for (size_t i = 1; i <= rectsTable.size(); i++)
	{
		sol::table t = rectsTable[i];
		int id = t.get_or(1, 0);
		auto p1 = t.get_or<std::array<float,2>>(2,{});
		auto p2 = t.get_or<std::array<float,2>>(3,{});
		float height = t.get_or(4,0.0f);
		int type = t.get_or(5,0);
		float dens = t.get_or(6,0.0f);
		float rest = t.get_or(7,0.0f);
		float fric = t.get_or(8,0.0f);
		float lDamp = t.get_or(9,0.0f);
		float aDamp = t.get_or(10,0.0f);

		PT<float> midpoint = {(p1[0] + p2[0])/2.0f, (p1[1] + p2[1])/2.0f };
		float length = sqrt( pow(p2[0] - p1[0],2) + pow(p2[1] - p1[1],2) );
		float angle = std::atan2( p2[1] - p1[1], p2[0] - p1[0] );

		b2PolygonShape polygonShape;
		polygonShape.SetAsBox(length*_box2dScale/2.0f,height*_box2dScale/2.0f);
		
		b2FixtureDef fixtureDef;
		fixtureDef.density = dens;
		fixtureDef.restitution = rest;
		fixtureDef.friction = fric;
		fixtureDef.shape = &polygonShape;

		b2BodyDef bodyDef;
		bodyDef.position.Set(midpoint.x*_box2dScale,midpoint.y*_box2dScale);
		bodyDef.type = (b2BodyType)type;
		bodyDef.angle = angle;
		_bodyPtrs[id] = _world->CreateBody(&bodyDef);
		_bodyPtrs[id]->CreateFixture(&fixtureDef);
		_bodyPtrs[id]->SetLinearDamping(lDamp);
		_bodyPtrs[id]->SetAngularDamping(aDamp);
		userdata.push_back(id);
		_bodyPtrs[id]->GetUserData().pointer = reinterpret_cast<uintptr_t>(&userdata.back());
	}
}

void PhysicalWorld::SpawnRectangle(int id, PT<float> p1, PT<float> p2, float height,
	int type, float dens, float rest, float fric, float lDamp, float aDamp, int* userdata)
{
	PT<float> midpoint = {(p1.x + p2.x)/2.0f, (p1.y + p2.y)/2.0f };
	float length = sqrt( pow(p2.x - p1.x,2) + pow(p2.y - p1.y,2) );
	float angle = std::atan2( p2.y - p1.y, p2.x - p1.x );

	b2PolygonShape polygonShape;
	polygonShape.SetAsBox(length*_box2dScale/2.0f,height*_box2dScale/2.0f);

	b2FixtureDef fixtureDef;
	fixtureDef.density = dens;
	fixtureDef.restitution = rest;
	fixtureDef.friction = fric;
	fixtureDef.shape = &polygonShape;

	b2BodyDef bodyDef;
	bodyDef.position.Set(midpoint.x*_box2dScale,midpoint.y*_box2dScale);
	bodyDef.type = (b2BodyType)type;
	bodyDef.angle = angle;
	_bodyPtrs[id] = _world->CreateBody(&bodyDef);
	_bodyPtrs[id]->CreateFixture(&fixtureDef);
	_bodyPtrs[id]->SetLinearDamping(lDamp);
	_bodyPtrs[id]->SetAngularDamping(aDamp);
	_bodyPtrs[id]->GetUserData().pointer = reinterpret_cast<uintptr_t>(userdata);
}

void PhysicalWorld::SpawnPolygon(int id, PT<float> midpoint, std::vector<PT<float>> localPts, 
	float angle, int type, float dens,
	float rest, float fric, float lDamp, float aDamp, int* userdata)
{
	b2PolygonShape polygonShape;
	b2Vec2* points = new b2Vec2[int(localPts.size())]();
	for (int i = 0; i < localPts.size(); i++)
	{
		points[i].Set(localPts[i].x*_box2dScale, localPts[i].y*_box2dScale);
	}
	polygonShape.Set(b2ComputeHull(points, int32(localPts.size())));
	delete[] points;

	b2FixtureDef fixtureDef;
	fixtureDef.density = dens;
	fixtureDef.restitution = rest;
	fixtureDef.friction = fric;
	fixtureDef.shape = &polygonShape;

	b2BodyDef bodyDef;
	bodyDef.position.Set(midpoint.x*_box2dScale,midpoint.y*_box2dScale);
	bodyDef.type = (b2BodyType)type;
	bodyDef.angle = angle;
	_bodyPtrs[id] = _world->CreateBody(&bodyDef);
	_bodyPtrs[id]->CreateFixture(&fixtureDef);
	_bodyPtrs[id]->SetLinearDamping(lDamp);
	_bodyPtrs[id]->SetAngularDamping(aDamp);
	_bodyPtrs[id]->GetUserData().pointer = reinterpret_cast<uintptr_t>(userdata);
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

void PhysicalWorld::SetBoostXY(const int id, const float forceX, const float forceY)
{
	b2Body* body = _bodyPtrs[id];
	b2Vec2 force(forceX, forceY);
	b2Vec2 point = body->GetWorldCenter();
	body->ApplyForce(force, point, true);
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
//	for (b2Fixture* fixture = body->GetFixtureList(); fixture; fixture = fixture->GetNext())
		b2Fixture* fixture = body->GetFixtureList();
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
	//for (b2Fixture* fixture = body->GetFixtureList(); fixture; fixture = fixture->GetNext())
	
		b2Fixture* fixture = body->GetFixtureList();
	
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

bool PhysicalWorld::IsBodyGrounded(const int id)
{
	return reinterpret_cast<PhysicalWorld::Userdata*>(_bodyPtrs[id]->GetUserData().pointer)->inContact;
}

void PhysicalWorld::SetListener(PhysicalWorld::ContactChecker* checker)
{
	_world->SetContactListener(checker);
}

void GroundedListener::BeginContact(b2Contact* contact)
{
	b2Body* bodyA = contact->GetFixtureA()->GetBody();
  b2Body* bodyB = contact->GetFixtureB()->GetBody();

	if ((bodyA->GetType() == b2_dynamicBody && bodyB->GetType() == b2_staticBody) ||
	    (bodyA->GetType() == b2_staticBody && bodyB->GetType() == b2_dynamicBody))
	{
		if (bodyA->GetType() == b2_dynamicBody)
		{
			_aInContact++;
			if (_aInContact == 1)
			{
				reinterpret_cast<PhysicalWorld::Userdata*>(bodyA->GetUserData().pointer)->inContact = true;
			}
		}
		else
		{
			_bInContact++;
			if (_bInContact == 1)
			{
				reinterpret_cast<PhysicalWorld::Userdata*>(bodyB->GetUserData().pointer)->inContact = true;
			}
		}
	}
}

void GroundedListener::EndContact(b2Contact* contact)
{
	b2Body* bodyA = contact->GetFixtureA()->GetBody();
  b2Body* bodyB = contact->GetFixtureB()->GetBody();

	if ((bodyA->GetType() == b2_dynamicBody && bodyB->GetType() == b2_staticBody) ||
	    (bodyA->GetType() == b2_staticBody && bodyB->GetType() == b2_dynamicBody))
	{
		if (bodyA->GetType() == b2_dynamicBody)
		{
			_aInContact--;
			if (_aInContact == 0)
			{
				reinterpret_cast<PhysicalWorld::Userdata*>(bodyA->GetUserData().pointer)->inContact = false;
			}
		}
		else
		{
			_bInContact--;
			if (_bInContact == 0)
			{
				reinterpret_cast<PhysicalWorld::Userdata*>(bodyB->GetUserData().pointer)->inContact = false;
			}
		}
	}
}

void PhysicalWorld::ContactChecker::BeginContact(b2Contact* contact)
{
	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();

	auto uA = reinterpret_cast<int*>(fixtureA->GetBody()->GetUserData().pointer);
	auto uB = reinterpret_cast<int*>(fixtureB->GetBody()->GetUserData().pointer);

	if (*uA == _id)
	{
		//std::cout << "Contact with " << *uB << std::endl;
		_idsInContactWith.push_back(*uB);
	}
	else if (*uB == _id)
	{
		//std::cout << "Contact with " << *uA << std::endl;
		_idsInContactWith.push_back(*uA);
	}
}

void PhysicalWorld::ContactChecker::EndContact(b2Contact* contact)
{
	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();

	auto uA = reinterpret_cast<int*>(fixtureA->GetBody()->GetUserData().pointer);
	auto uB = reinterpret_cast<int*>(fixtureB->GetBody()->GetUserData().pointer);

	if (*uA == _id)
	{
		//std::cout << "End Contact with " << *uB << std::endl;
		_idsInContactWith.erase(std::remove(
			_idsInContactWith.begin(), _idsInContactWith.end(), *uB),
			_idsInContactWith.end());
	}
	else if (*uB == _id)
	{
		//std::cout << "End Contact with " << *uA << std::endl;
		_idsInContactWith.erase(std::remove(
			_idsInContactWith.begin(), _idsInContactWith.end(), *uA),
			_idsInContactWith.end());
	}
}

bool PhysicalWorld::ContactChecker::IsInContactWithId(int lessThan, int moreThan)
{
	return std::find_if(_idsInContactWith.begin(), _idsInContactWith.end(),
		[=](int id){ return id < lessThan && id > moreThan; })
			!= _idsInContactWith.end();
}
