#include "game.hpp"


/**
 * Builds out the maze using the environment configuration provided.
 * @param cfg EnvConfig - Configuration defining how the maze world is layed out, and its entities.
 * @returns bool - true on success, false otherwise.
 */
bool Game::buildMaze(EnvConfig cfg) {

	EnvConfig::tMazeRows rows = cfg.getMazeRows();

	// // Loop over the rows and put them into layers
	// for (int idx=1; idx <= rows.size(); idx++) {
	// 	if (!(idx % dim.depth)) {
	// 		cout << "new layer added" << endl;
	// 	}
	// }

}



/**
 * Starts the simulation step which will move the enitites through the maze trying to find the exit.
 * This will run until the simulation either fails to find an exit, or the entities exit.
 */
void Game::run() {};