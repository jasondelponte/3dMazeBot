#ifndef _BOT_HPP_
#define _BOT_HPP_

#include "maze.hpp"
#include "pathfind.hpp"

#include <vector>
#include <string>

class Bot {
public:

	/**
	 * Initialize the bot and its starting location
	 * @param the maze the bot will be using to travel through
	 * @param current location of the bot in the grid.
	 */
	Bot(Maze* pMaze, Maze::tCoord loc);

	/**
	 * Attempts to find a rout from the bot's current location
	 * to the coordinate specified. Using the grid to naviage through
	 * @param dest - Coordinate of the destination
	 * @returns true if a route can be found,false otherwise.
	 */
	bool calcRoute(Maze::tCoord dest);

	/**
	 * Returns a string of the the bot used so far along its
	 * path to reach the destination
	 * @returns string of the route used. "N,S,E,W,U,D";
	 */
	std::string getRouteUsed();

	/**
	 * Moves the bot one step along the route that was calculated 
	 * earlier with calcRoute().
	 * @returns if the bot moved.
	 */
	bool move();

	/**
	 * Returns a copy of the Bot's current coordinat location
	 * @returns current location
	 */
	Maze::tCoord getLoc() { return m_curLoc; };

private:
	// Current location on the grid of this bot
	Maze::tCoord m_curLoc;
	Maze::tCoord m_destLoc;

	// Maze reference
	Maze* m_pMaze;

	// Pathfinder to find the route between 
	// two coordiantes on the grid
	PathFind m_pathfinder;

	// The route to reach the destination
	PathFind::tRoute m_route;

	// list of the route used
	std::vector<char> m_routeUsed;
};

#endif // !defined(_BOT_HPP_)
