#ifndef __PFADFINDUNG_HPP
#define __PFADFINDUNG_HPP

#include <climits>
#include <game/coordinates.hpp>
#include <vector>

namespace stemaj {

		static PT<int> toGridPoint(PT<int> gridDimension, PT<int> displaySize, PT<int> point)
		{
			int singleWidth = displaySize.x / gridDimension.x;
			int singleHeight = displaySize.y / gridDimension.y;
			int minDistance = INT_MAX;
			PT<int> ret = { -1,-1 };
			for (int y = singleHeight / 2; y <= displaySize.y - (singleHeight / 2); y = y + singleHeight)
				for (int x = singleWidth / 2; x <= displaySize.x - (singleWidth / 2); x = x + singleWidth)
				{
					int distance = CO.Distance(point, { x,y });
					if (distance < minDistance)
					{
						minDistance = distance;
						ret = {x,y};
					}
				}
			return ret;
		}

// Pathfinding class implementing the A* algorithm
class Pathfinding {
public:
explicit Pathfinding();
virtual ~Pathfinding() = default;
std::vector<PT<int>> FindPath(PT<int> start, PT<int> end);
void SetGrid(int height, int width);
void ToggleObstacle(int x, int y);

private:

	struct sNode
	{
		bool bObstacle = false;			// Is the node an obstruction?
		bool bVisited = false;			// Have we searched this node before?
		float fGlobalGoal;				// Distance to goal so far
		float fLocalGoal;				// Distance to goal if we took the alternative route
		int x;							// Nodes position in 2D space
		int y;
		std::vector<sNode*> vecNeighbours;	// Connections to neighbours
		sNode* parent;					// Node connecting to this node that offers shortest parent
	};


bool Solve_AStar();
	sNode *nodes = nullptr;
	int nMapWidth = 10;
	int nMapHeight = 10;

	sNode *nodeStart = nullptr;
	sNode *nodeEnd = nullptr;
};

}

#endif //__PFADFINDUNG_HPP