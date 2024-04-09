#ifndef __PFADFINDUNG_HPP
#define __PFADFINDUNG_HPP

#include <vector>

namespace stemaj {


// Pathfinding class implementing the A* algorithm
class Pathfinding {
public:
 struct Point {
    int x, y;
    Point(int _x, int _y) : x(_x), y(_y) {}
  };
explicit Pathfinding();
virtual ~Pathfinding() = default;
std::vector<Point> FindPath(Point start, Point end);
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