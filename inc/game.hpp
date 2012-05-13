#ifndef _GAME_HPP_
#define _GAME_HPP_

#include "env_config.hpp"
#include "maze.hpp"
#include "bot.hpp"

class Game {
public:
	Game();

	/**
	 * Builds out the maze using the environment configuration provided.
	 * @param cfg EnvConfig - Configuration defining how the maze world is layed out, and its entities.
	 * @returns bool - true on success, false otherwise.
	 */
	bool buildEnv(EnvConfig cfg);

	/**
	 * Starts the simulation step which will move the enitites through the maze trying to find the exit.
	 * This will run until the simulation either fails to find an exit, or the entities exit.
	 */
	void run();

private:
	// Game board that the bot will move through.
	Maze* m_pMaze;

	// Reference to the bot that will travel the maze
	Bot* m_pBot;

	// Location of the exit point on the maze
	Maze::tCoord m_ExitCell;

	/**
	 * Initializes the maze cells with the state from the configuration file
	 * @param pMaze - pointer to the maze instance
	 * @param rows - List of rows to set the maze's state with.
 	 * @param dim - dimensions of the maze
	 */
	void initMazeCellsState(Maze* pMaze, EnvConfig::tMazeRows row, Maze::tDimension dim);
};

#endif // !defined(_GAME_HPP_)