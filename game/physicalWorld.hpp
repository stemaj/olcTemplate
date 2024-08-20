#ifndef __PHYSICALWORLD_HPP
#define __PHYSICALWORLD_HPP

#include <olcTemplate/sdk/box2d/include/box2d.h>
#include <olcTemplate/game/coordinates.hpp>
#include <string>
#include <unordered_map>

namespace stemaj {

struct PhysicalRectangle
{
	int id;
	float x;
	float y;
	float w;
	float h;
};

class PhysicalWorld
{
public:
	virtual ~PhysicalWorld();
	
	void LoadFromScript(const std::string& name, const std::string& prefix);
	
	void Step(float fElapsedTime);

	PT<float> GetCenterPoint(const int id);
	
	std::unordered_map<int, std::vector<PT<float>>> GetPolygons();
	std::unordered_map<int, std::pair<PT<float>,float>> GetCircles();
	std::unordered_map<int, std::pair<PT<float>,PT<float>>> GetEdges();
	std::unordered_map<int, std::vector<PT<float>>> GetChains();

	std::vector<PT<float>> GetPolygonVertex(const int id);
	std::pair<PT<float>,float> GetCirclePosAndRadius(const int id);
	std::pair<PT<float>,PT<float>> GetEdgeEndpoints(const int id);
	std::vector<PT<float>> GetChainVertex(const int id);

	void SetBoostX(const int id, const float forceX, const float maxSpeedX);

	float GetSpeedX(const int id);
private:

	float _box2dScale = 0.0f;
	
	std::unordered_map<int, b2Body*> _bodyPtrs;
	std::unique_ptr<b2World> _world;
};

} // stemaj

#endif // __PHYSICALWORLD_HPP
