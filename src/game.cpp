#include "game.hpp"

#include <iostream>

using namespace std;

/**
 * Initializes tha game so it can be built
 */
Game::Game(): m_pMaze(NULL) {}

/**
 * Cleans up any memeory allocated remaning
 */
Game::~Game() {
	cleanup();
}

/**
 * Builds out the maze using the environment configuration provided.
 * @param cfg EnvConfig - Configuration defining how the maze world is layed out, and its entities.
 * @returns bool - true on success, false otherwise.
 */
bool Game::buildEnv(EnvConfig cfg) {
	EnvConfig::tMazeRows rows = cfg.getMazeRows();

	Maze::tDimension dim = cfg.getDim();
	m_pMaze = new Maze(dim);

	createBots(cfg.getBotCoords());
	m_ExitCoord = cfg.getExitCoord();

	initMazeCellsState(m_pMaze, rows, dim);
}

/**
 * Creates the bots from the entity maping provided.
 * @param coords map of symbol and grid coordinates for each bot.
 */
void Game::createBots(EnvConfig::tBotCoords coords) {
	EnvConfig::tBotCoords::const_iterator cIt;
	for (cIt = coords.begin(); cIt != coords.end(); cIt++) {
		m_bots[(*cIt).first] = new Bot(m_pMaze, (*cIt).second);
	}
}

/**
 * Starts the simulation step which will move the enitites through the maze trying to find the exit.
 * This will run until the simulation either fails to find an exit, or the entities exit.
 * @returns true if the maze was successfuly solved. false otherwise.
 */
bool Game::run() {
	// init the bot's by calculating their routes
	initBots();

	// Step through the simulation telling the bot to move through the maze
	while(m_bots.size() > 0) {
		tBots::iterator it;
		for (it = m_bots.begin(); it != m_bots.end(); it++) {
			Bot* pBot = (*it).second;

			if (!pBot->move()) {
				cerr << "Bot [" << (*it).first << "], didn't move, waiting a turn." << endl;
				continue;
			}

			if (pBot->getLoc() == m_ExitCoord) {
				cout << "Bot [" << (*it).first << "], Escapable: " << pBot->getRouteUsed() << endl;
				m_bots.erase(it);
			}
		}

		// m_pMaze->printLayer(m_pBot->getLoc().y);
	}

	return true;
};

/**
 * Calculate the bot's initialize route through the maze. If a bot is unable to find
 * a path to the exit, it will be removed from the game.
 * @returns if any of the buts were able to find a route
 */
void Game::initBots() {
	tBots::iterator it;
	for (it = m_bots.begin(); it != m_bots.end(); it++) {
		Bot* pBot = (*it).second;
		if (!pBot->calcRoute(m_ExitCoord)) {
			cerr << "Bot [" << (*it).first << "], Not Escapable." << endl;
			m_bots.erase(it);
		}
	}
}

/**
 * Initializes the maze cells with the state from the configuration file
 * @param pMaze - pointer to the maze instance
 * @param rows - List of rows to set the maze's state with.
 * @param dim - dimensions of the maze
 */
void Game::initMazeCellsState(Maze* pMaze, EnvConfig::tMazeRows rows, Maze::tDimension dim) {
	int rowIdx = 0;
	EnvConfig::tMazeRows::const_iterator cIt;
	for (cIt = rows.begin(); cIt != rows.end(); cIt++) {
		EnvConfig::tMazeRow row = *cIt;

		int x = 0;
		EnvConfig::tMazeRow::const_iterator cRowIt;
		for (cRowIt = row.begin(); cRowIt != row.end(); cRowIt++) {
			// Get the cell, and using the env configs method to calculate the cords of the cell which needs to be updated
			Maze::eCell cell = *cRowIt;
			if (cell != Maze::CELL_EMPTY) {
				Maze::tCoord coord = EnvConfig::calcCoordFromRowDim(x, rowIdx, dim);
				pMaze->updateCell(coord, cell);
			}
			x++;
		}
		rowIdx++;
	}
}

/**
 * Deletes any allocated memory used during run
 */
void Game::cleanup() {
	if (m_pMaze != NULL) {
		delete m_pMaze;
		m_pMaze = NULL;
	}

	tBots::iterator it;
	for (it = m_bots.begin(); it != m_bots.end(); it++) {
		Bot* pBot = (*it).second;
		delete pBot;
		m_bots.erase(it);
	}
}
