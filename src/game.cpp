#include "game.hpp"

#include <iostream>

using namespace std;

/**
 * Initializes tha game so it can be built
 */
Game::Game(): m_pMaze(NULL), m_pBot(NULL) {}

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

	m_pBot = new Bot(m_pMaze, cfg.getBotCoord());

	m_ExitCoord = cfg.getExitCoord();

	initMazeCellsState(m_pMaze, rows, dim);
}

/**
 * Starts the simulation step which will move the enitites through the maze trying to find the exit.
 * This will run until the simulation either fails to find an exit, or the entities exit.
 * @returns true if the maze was successfuly solved. false otherwise.
 */
bool Game::run() {
	// Calculate the bot's initialize route through the maze. If it is unable to find a path
	// we'll know here and can stop before we start moving the bot.
	if (!m_pBot->calcRoute(m_ExitCoord)) {
		cerr << "Not Escapable" << endl;
		return false;
	}

	// Step through the simulation telling the bot to move through the maze
	while(m_pBot->getLoc() != m_ExitCoord) {
		if (!m_pBot->move()) {
			cerr << "Bot didn't move, quiting" << endl;
			return false;
		}

		m_pMaze->printLayer(m_pBot->getLoc().y);
	}

	cout << "Escapable: " << m_pBot->getRouteUsed() << endl;
	return true;
};

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
	if (m_pBot != NULL) {
		delete m_pBot;
		m_pBot = NULL;
	}
}
