#include "bot.hpp"

#include <iostream>

using namespace std;

/**
 * Initialize the bot and its starting 
 * @param the maze the bot will be using to travel through
 * @param current location of the bot in the grid.
 */
Bot::Bot(Maze* pMaze, Maze::tCoord loc): m_pMaze(pMaze), m_curLoc(loc) {
	m_pathfinder.setGrid(pMaze->getGrid());
	m_pathfinder.setLoc(m_curLoc);
}

/**
 * Attempts to find a rout from the bot's current location
 * to the coordinate specified. Using the grid to naviage through
 * @param dest - Coordinate of the destination
 * @returns true if a route can be found,false otherwise.
 */
bool Bot::calcRoute(Maze::tCoord dest) {
	m_destLoc = dest;
	PathFind::tRoute route = m_pathfinder.findRoute(dest);
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
	vector<char>::const_iterator cIt;
	string routeUsed;
	for (cIt=m_routeUsed.begin(); cIt != m_routeUsed.end(); cIt++) {
		routeUsed += (char)*cIt;
	}

	return routeUsed;
}

/**
 * Moves the bot one step along the route that was calculated 
 * earlier with calcRoute().
 * @returns if the bot moved.
 */
bool Bot::move() {
	if (m_route.empty()) {
		return false;
	}

	Maze::tCell* cell = m_route.top();
	// Make sure we are actually moving
	if (cell->coord == m_curLoc) {
		m_route.pop();
		return false;
	}

	// Make sure our next destination is valid
	if (cell->state == Maze::CELL_SOLID || cell->state == Maze::CELL_OCCUPIED) {
		// No need to pop the stack here since we'll be trying this cell again next round.
		return false;
	}

	// Keep track of our current route
	m_routeUsed.push_back(m_curLoc.direction(cell->coord));

	// Update the cells to our position in the maze, don't reset the exit cell' state
	if (cell->state != Maze::CELL_EXIT) {
		m_pMaze->updateCell(cell->coord, Maze::CELL_OCCUPIED);
	}
	m_pMaze->updateCell(m_curLoc, Maze::CELL_EMPTY);

	m_curLoc = cell->coord;

	m_route.pop();
	return true;
}
