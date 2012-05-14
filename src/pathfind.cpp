#include "pathfind.hpp"

#include <stdlib.h>
#include <queue>

using namespace std;

/**
 * Initializes the Path finder with the grid of the maze, and 
 * the starting location of the entity the route will be 
 * calculated for.
 */
PathFind::PathFind(): m_pGrid(NULL) {}

/**
 * Sets the grid the pathfinder should use when searching for routes
 * Setting a grid will invalidate any precalculated route trees.
 * @param maze grid
 */
void PathFind::setGrid(Maze::tGrid* pGrid) {
	m_pGrid = pGrid;
}

/**
 * The location of the entity has changed.
 * @param loc - new location of entity
 */
void PathFind::setLoc(Maze::tCoord loc) {
	m_curLoc = loc;
}

/**
 * Generates a mapping of the grid if one hasn't been generated yet,
 * and searches through the grid for the destintion provided. If
 * The destintaion is unreachable a empty route will be returned.
 * @param dest - Coordinate of the destination 
 * @returns the route in cells the 
 */
PathFind::tRoute PathFind::findRoute(Maze::tCoord dest) {
	tRoute route;

	// If we don't have a grid we cannot calculate a route
	if (m_pGrid == NULL || m_curLoc == dest) { return route; }

	// Genreate the path tree to the destination
	PathTree* pDestNode = generatePathTree(m_curLoc, dest);
	if (pDestNode != NULL) {
		// Walk up the true, building the route that needs to be taken.
		// Don't include the last node in the route, since that is our current loc
		while (pDestNode->getParent() != NULL) {
			route.push(pDestNode->getCell());
			pDestNode = pDestNode->getParent();
		}
	}

	return route;
}


/**
 * Search over the grid, building the tree starting at the current location.
 * The pathfinder's current location and grid are used to generate the tree.
 * @param from starting point in the grid.
 * @param dest destination the routes are being generated to reach.
 * @returns the tree of routes.
 */
PathTree* PathFind::generatePathTree(Maze::tCoord from, Maze::tCoord dest) {
	PathTree* root = new PathTree(NULL, m_pGrid->at(from));
	tTreeNodeQueue nodeQ;
	nodeQ.push(root);

	PathTree* pNode = NULL;
	while (!nodeQ.empty()) {
		pNode = nodeQ.front();
		nodeQ.pop();

		if (*pNode == dest) { break; }
		// Get the 6 adjacent cells adding them to the tree Only add cells which are not solid.  If the cell
		// is the destination terminate there.

		Maze::tCoord curCoord = pNode->getCell()->coord;
		queueValidNodeAtCoord(pNode, curCoord + Maze::tCoord(0,0,-1), nodeQ); // North
		queueValidNodeAtCoord(pNode, curCoord + Maze::tCoord(0,0,1), nodeQ);  // South
		queueValidNodeAtCoord(pNode, curCoord + Maze::tCoord(1,0,0), nodeQ);  // East
		queueValidNodeAtCoord(pNode, curCoord + Maze::tCoord(-1,0,0), nodeQ); // West
		queueValidNodeAtCoord(pNode, curCoord + Maze::tCoord(0,1,0), nodeQ);  // Up
		queueValidNodeAtCoord(pNode, curCoord + Maze::tCoord(0,-1,0), nodeQ); // Down

		pNode = NULL;
	}

	return pNode;
}

/**
 * Queues up a new node, while also adding it to the node tree.
 * @param parent node in the tree this is being appened to.
 * @param new coord to get get the cell from
 * @param queye where the node will be added to, if valid
 * @returns the node if it was created, and it is not already an ancestor.
 */
PathTree* PathFind::queueValidNodeAtCoord(PathTree* pParent, Maze::tCoord coord, tTreeNodeQueue &nodeQ) {
	Maze::tCell* pCell = m_pGrid->at(coord);

	 // Make sure we didn't go out of bounds, and the cell is one we care about.
	if (pCell == NULL || pCell->state == Maze::CELL_SOLID || pCell->state == Maze::CELL_OCCUPIED) {
		return NULL;
	}

	// The add child will return null, if the child already exists as an ancestor to the parent.
	PathTree* pNode = pParent->addChild(pCell);
	if (pNode != NULL) {
		nodeQ.push(pNode);
	}
	return pNode;
}
