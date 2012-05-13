#ifndef _PATHFIND_HPP_
#define _PATHFIND_HPP_

#include "maze.hpp"

#include <stack>

class PathFind {
public:
	struct tWaypoint {
		Maze::tCell* pCell;
		char dir;
		tWaypoint(Maze::tCell* c=NULL, char d='X'): pCell(c), dir(d) {};
	};

	// Route that should be used
	typedef std::stack<Maze::tCell> tRoute;

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
	void setGrid(Maze::tGrid* grid);

	/**
	 * Generates a mapping of the grid if one hasn't been generated yet,
	 * and searches through the grid for the destintion provided. If
	 * The destintaion is unreachable a empty route will be returned.
	 * @param dest - Coordinate of the destination 
	 * @returns the route in cells the 
	 */
	tRoute findRoute(Maze::tCoord loc, Maze::tCoord dest);

private:
};

#endif // !defined(_PATHFIND_HPP_)
