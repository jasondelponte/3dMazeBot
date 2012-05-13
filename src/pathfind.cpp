#include "pathfind.hpp"


/**
 * Initializes the Path finder with the grid of the maze, and 
 * the starting location of the entity the route will be 
 * calculated for.
 */
PathFind::PathFind() {

}

/**
 * Sets the grid the pathfinder should use when searching for routes
 * Setting a grid will invalidate any precalculated route trees.
 * @param maze grid
 */
void PathFind::setGrid(Maze::tGrid* grid) {

}

/**
 * Generates a mapping of the grid if one hasn't been generated yet,
 * and searches through the grid for the destintion provided. If
 * The destintaion is unreachable a empty route will be returned.
 * @param dest - Coordinate of the destination 
 * @returns the route in cells the 
 */
PathFind::tRoute PathFind::findRoute(Maze::tCoord loc, Maze::tCoord dest) {
	return tRoute();
}
