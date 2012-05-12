#ifndef _GAME_HPP_
#define _GAME_HPP_

#include "env_config.hpp"
#include "maze.hpp"

class Game {
public:
	/**
	 * Builds out the maze using the environment configuration provided.
	 * @param cfg EnvConfig - Configuration defining how the maze world is layed out, and its entities.
	 * @returns bool - true on success, false otherwise.
	 */
	bool buildMaze(EnvConfig cfg);

	/**
	 * Starts the simulation step which will move the enitites through the maze trying to find the exit.
	 * This will run until the simulation either fails to find an exit, or the entities exit.
	 */
	void run();

private:

};

#endif // !defined(_GAME_HPP_)