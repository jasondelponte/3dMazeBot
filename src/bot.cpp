#include "bot.hpp"

using namespace std;

/**
 * Initialize the bot and its starting 
 * @param grid of the mazze the bot will be using to travel through
 * @param current location of the bot in the grid.
 */
Bot::Bot(Maze::tGrid* pGrid, Maze::tCoord loc): m_curLoc(loc) {
	m_pathfinder.setGrid(pGrid);
}

/**
 * Attempts to find a rout from the bot's current location
 * to the coordinate specified. Using the grid to naviage through
 * @param dest - Coordinate of the destination
 * @returns true if a route can be found,false otherwise.
 */
bool Bot::calcRoute(Maze::tCoord dest) {
	m_destLoc = dest;
	PathFind::tRoute route = m_pathfinder.findRoute(m_curLoc, dest);
	if (route.empty()) {
		return false;
	}

	m_route = route;
	return true;
}

/**
 * Returns a string of the the bot used so far along its
 * path to reach the destination
 * @returns string of the route used. "N,S,E,W,U,D";
 */
string Bot::getRouteUsed() {
	return "";
}

/**
 * Moves the bot one step along the route that was calculated 
 * earlier with calcRoute().
 * @returns if the bot moved.
 */
bool Bot::move() {
	if (m_route.empty() && m_curLoc != m_destLoc) {
		return false;
	}

	return false;
}
