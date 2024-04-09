#include <algorithm>
#include <cmath>
#include <list>
#include <iostream>
#ifdef RUN_TESTS
#include <sdk/doctest-2.4.11/doctest.h>
#endif
#include <game/src/tools/jumpPointSearch.hpp>

using namespace stemaj;
using Point = Pathfinding::Point;

Pathfinding::Pathfinding()
{
    	// Create a 2D array of nodes - this is for convenience of rendering and construction
		// and is not required for the algorithm to work - the nodes could be placed anywhere
		// in any space, in multiple dimensions...
		nodes = new sNode[nMapWidth * nMapHeight];
		for (int x = 0; x < nMapWidth; x++)
			for (int y = 0; y < nMapHeight; y++)
			{
				nodes[y * nMapWidth + x].x = x; // ...because we give each node its own coordinates
				nodes[y * nMapWidth + x].y = y;
				nodes[y * nMapWidth + x].bObstacle = false;
				nodes[y * nMapWidth + x].parent = nullptr;
				nodes[y * nMapWidth + x].bVisited = false;
			}

		// Create connections - in this case nodes are on a regular grid
		for (int x = 0; x < nMapWidth; x++)
			for (int y = 0; y < nMapHeight; y++)
			{
				if(y>0)
					nodes[y*nMapWidth + x].vecNeighbours.push_back(&nodes[(y - 1) * nMapWidth + (x + 0)]);
				if(y<nMapHeight-1)
					nodes[y*nMapWidth + x].vecNeighbours.push_back(&nodes[(y + 1) * nMapWidth + (x + 0)]);
				if (x>0)
					nodes[y*nMapWidth + x].vecNeighbours.push_back(&nodes[(y + 0) * nMapWidth + (x - 1)]);
				if(x<nMapWidth-1)
					nodes[y*nMapWidth + x].vecNeighbours.push_back(&nodes[(y + 0) * nMapWidth + (x + 1)]);

				// We can also connect diagonally
				if (y>0 && x>0)
					nodes[y*nMapWidth + x].vecNeighbours.push_back(&nodes[(y - 1) * nMapWidth + (x - 1)]);
				if (y<nMapHeight-1 && x>0)
					nodes[y*nMapWidth + x].vecNeighbours.push_back(&nodes[(y + 1) * nMapWidth + (x - 1)]);
				if (y>0 && x<nMapWidth-1)
					nodes[y*nMapWidth + x].vecNeighbours.push_back(&nodes[(y - 1) * nMapWidth + (x + 1)]);
				if (y<nMapHeight - 1 && x<nMapWidth-1)
					nodes[y*nMapWidth + x].vecNeighbours.push_back(&nodes[(y + 1) * nMapWidth + (x + 1)]);
				
			}

		// Manually positio the start and end markers so they are not nullptr
		nodeStart = &nodes[(nMapHeight / 2) * nMapWidth + 1];
		nodeEnd = &nodes[(nMapHeight / 2) * nMapWidth + nMapWidth-2];
}

void Pathfinding::SetGrid(int height, int width)
{
  nMapWidth = width;
	nMapHeight = height;

}

void Pathfinding::ToggleObstacle(int nSelectedNodeX, int nSelectedNodeY)
{
	nodes[nSelectedNodeY * nMapWidth + nSelectedNodeX].bObstacle = !nodes[nSelectedNodeY * nMapWidth + nSelectedNodeX].bObstacle;
}

std::vector<Point> Pathfinding::FindPath(Point start, Point end)
{
	std::vector<Point> ret;
	nodeStart = &nodes[start.y * nMapWidth + start.x];
	nodeEnd = &nodes[end.y * nMapWidth + end.x];
	if(nodeStart->x >=0 && nodeStart->x < nMapWidth)
		if (nodeStart->y >= 0 && nodeStart->y < nMapHeight)
			if(nodeEnd->x >=0 && nodeEnd->x < nMapWidth)
				if (nodeEnd->y >= 0 && nodeEnd->y < nMapHeight)
					if (Solve_AStar()) // Solve in "real-time" gives a nice effect
					{
						if (nodeEnd != nullptr)
						{
							sNode *p = nodeEnd;
							ret.push_back(Point(p->x,p->y));
							while (p->parent != nullptr)
							{
								ret.push_back(Point(p->parent->x, p->parent->y));
								
								// Set next node to this node's parent
								p = p->parent;
							}
						}
					}
	std::reverse(ret.begin(), ret.end());
	return ret;
}


bool Pathfinding::Solve_AStar()
	{
		// Reset Navigation Graph - default all node states
		for (int x = 0; x < nMapWidth; x++)
			for (int y = 0; y < nMapHeight; y++)
			{
				nodes[y*nMapWidth + x].bVisited = false;
				nodes[y*nMapWidth + x].fGlobalGoal = INFINITY;
				nodes[y*nMapWidth + x].fLocalGoal = INFINITY;
				nodes[y*nMapWidth + x].parent = nullptr;	// No parents
			}

		auto distance = [](sNode* a, sNode* b) // For convenience
		{
			return sqrtf((a->x - b->x)*(a->x - b->x) + (a->y - b->y)*(a->y - b->y));
		};

		auto heuristic = [distance](sNode* a, sNode* b) // So we can experiment with heuristic
		{
			return distance(a, b);
		};

		// Setup starting conditions
		sNode *nodeCurrent = nodeStart;
		nodeStart->fLocalGoal = 0.0f;
		nodeStart->fGlobalGoal = heuristic(nodeStart, nodeEnd);

		// Add start node to not tested list - this will ensure it gets tested.
		// As the algorithm progresses, newly discovered nodes get added to this
		// list, and will themselves be tested later
		std::list<sNode*> listNotTestedNodes;
		listNotTestedNodes.push_back(nodeStart);

		// if the not tested list contains nodes, there may be better paths
		// which have not yet been explored. However, we will also stop 
		// searching when we reach the target - there may well be better
		// paths but this one will do - it wont be the longest.
		while (!listNotTestedNodes.empty() && nodeCurrent != nodeEnd)// Find absolutely shortest path // && nodeCurrent != nodeEnd)
		{
			// Sort Untested nodes by global goal, so lowest is first
			listNotTestedNodes.sort([](const sNode* lhs, const sNode* rhs){ return lhs->fGlobalGoal < rhs->fGlobalGoal; } );
			
			// Front of listNotTestedNodes is potentially the lowest distance node. Our
			// list may also contain nodes that have been visited, so ditch these...
			while(!listNotTestedNodes.empty() && listNotTestedNodes.front()->bVisited)
				listNotTestedNodes.pop_front();

			// ...or abort because there are no valid nodes left to test
			if (listNotTestedNodes.empty())
				break;

			nodeCurrent = listNotTestedNodes.front();
			nodeCurrent->bVisited = true; // We only explore a node once
			
					
			// Check each of this node's neighbours...
			for (auto nodeNeighbour : nodeCurrent->vecNeighbours)
			{
				// ... and only if the neighbour is not visited and is 
				// not an obstacle, add it to NotTested List
				if (!nodeNeighbour->bVisited && nodeNeighbour->bObstacle == 0)
					listNotTestedNodes.push_back(nodeNeighbour);

				// Calculate the neighbours potential lowest parent distance
				float fPossiblyLowerGoal = nodeCurrent->fLocalGoal + distance(nodeCurrent, nodeNeighbour);

				// If choosing to path through this node is a lower distance than what 
				// the neighbour currently has set, update the neighbour to use this node
				// as the path source, and set its distance scores as necessary
				if (fPossiblyLowerGoal < nodeNeighbour->fLocalGoal)
				{
					nodeNeighbour->parent = nodeCurrent;
					nodeNeighbour->fLocalGoal = fPossiblyLowerGoal;

					// The best path length to the neighbour being tested has changed, so
					// update the neighbour's score. The heuristic is used to globally bias
					// the path algorithm, so it knows if its getting better or worse. At some
					// point the algo will realise this path is worse and abandon it, and then go
					// and search along the next best path.
					nodeNeighbour->fGlobalGoal = nodeNeighbour->fLocalGoal + heuristic(nodeNeighbour, nodeEnd);
				}
			}	
		}

		return true;
	}

#ifdef RUN_TESTS
TEST_CASE("Testing Pathfinding") {
  Pathfinding jps;
  jps.SetGrid(10, 10);

  // std::vector<Point> polygon = {Point(3, 3), Point(3, 4), Point(6, 4), Point(6, 3)};
  // jps.SetPolygon(polygon);
	jps.ToggleObstacle(3,2);
	jps.ToggleObstacle(4,2);
	jps.ToggleObstacle(3,3);
	jps.ToggleObstacle(4,3);
	jps.ToggleObstacle(3,4);
	jps.ToggleObstacle(4,4);
	jps.ToggleObstacle(3,5);
	jps.ToggleObstacle(4,5);

  SUBCASE("Test FindPath with valid start and end points") {
    Point start(0, 0);
    Point end(9, 9);
    std::vector<Point> path = jps.FindPath(start, end);

    // fastest way around polygon
    REQUIRE(path.size() == 13);

		for (int i = 0; i< 13; i++)
		{
			std::cout << "x: "<< path[i].x << ", y: " << path[i].y << std::endl;
		}

    CHECK(path[0].x == start.x);
    CHECK(path[0].y == start.y);
    CHECK(path[path.size() - 1].x == end.x);
    CHECK(path[path.size() - 1].y == end.y);
  }

  SUBCASE("Test FindPath with invalid end point") {
    Point start(0, 0);
    Point end(3, 2); // Inside polygon
    std::vector<Point> path = jps.FindPath(start, end);
    REQUIRE(path.size() == 4);
  }
}
#endif //RUN_TESTS