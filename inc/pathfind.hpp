#ifndef _PATHFIND_HPP_
#define _PATHFIND_HPP_

#include "pathtree.hpp"
#include "maze.hpp"

#include <stack>
#include <queue>

class PathFind {
public:
	// Route that should be used
	typedef std::stack<Maze::tCell*> tRoute;
	typedef std::queue<PathTree*> tTreeNodeQueue;

	/**
	 * Initializes the Path finder with the grid of the maze, and 
	 * the starting location of the entity the route will be 
	 * calculated for.
	 */
	PathFind();

	/**
	 * Sets the grid the pathfinder should use when searching for routes
	 * Setting a grid will invalidate any precalculated route trees.
	 * @param maze grid
	 */
	void setGrid(Maze::tGrid* pGrid);

	/**
	 * The location of the entity has changed.  Update the route tree
	 * to reflect this.
	 * @param loc - new location of entity
	 */
	void setLoc(Maze::tCoord loc);

	/**
	 * Deletes all currently generated routes so new will be calculated next
	 * findRoute().
	 */
	void clearRoutes();

	/**
	 * Generates a mapping of the grid if one hasn't been generated yet,
	 * and searches through the grid for the destintion provided. If
	 * The destintaion is unreachable a empty route will be returned.
	 * @param dest - Coordinate of the destination 
	 * @returns the route in cells the 
	 */
	tRoute findRoute(Maze::tCoord dest);
	
private:
	Maze::tGrid* m_pGrid;
	Maze::tCoord m_curLoc;

	/**
	 * Iterates over the grid, building the tree starting at the current location.
	 * The pathfinder's current location and grid are used to generate the tree.
	 * @param from starting point in the grid.
	 * @param dest destination the routes are being generated to reach.
	 * @returns the tree of routes.
	 */
	PathTree* generatePathTree(Maze::tCoord from, Maze::tCoord dest);

	/**
	 * Queues up a new node, while also adding it to the node tree.
	 * @param parent node in the tree this is being appened to.
	 * @param new coord to get get the cell from
	 * @param queye where the node will be added to, if valid
	 * @returns the node if it was created, and it is not already an ancestor.
	 */
	PathTree* queueValidNodeAtCoord(PathTree* pParent, Maze::tCoord coord, tTreeNodeQueue &nodeQ);

};

#endif // !defined(_PATHFIND_HPP_)
