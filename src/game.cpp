#include "game.hpp"


Game::Game(): m_pMaze(NULL), m_pBot(NULL) {}

/**
 * Builds out the maze using the environment configuration provided.
 * @param cfg EnvConfig - Configuration defining how the maze world is layed out, and its entities.
 * @returns bool - true on success, false otherwise.
 */
bool Game::buildEnv(EnvConfig cfg) {
	EnvConfig::tMazeRows rows = cfg.getMazeRows();

	m_pBot = new Bot(cfg.getBotCoord());
	m_ExitCell = cfg.getExitCoord();

	Maze::tDimension dim = cfg.getDim();
	Maze* pMaze = new Maze(dim);

	initMazeCellsState(pMaze, rows, dim);
}

/**
 * Starts the simulation step which will move the enitites through the maze trying to find the exit.
 * This will run until the simulation either fails to find an exit, or the entities exit.
 */
void Game::run() {
	
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