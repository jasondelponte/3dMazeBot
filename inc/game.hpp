#ifndef _GAME_HPP_
#define _GAME_HPP_

#include "env_config.hpp"
#include "maze.hpp"
#include "bot.hpp"

class Game {
public:
	/**
	 * Initializes tha game so it can be built
	 */
	Game();

	/**
	 * Cleans up any memeory allocated remaning
	 */
	~Game();

	/**
	 * Builds out the maze using the environment configuration provided.
	 * @param cfg EnvConfig - Configuration defining how the maze world is layed out, and its entities.
	 * @returns bool - true on success, false otherwise.
	 */
	bool buildEnv(EnvConfig cfg);

	/**
	 * Starts the simulation step which will move the enitites through the maze trying to find the exit.
	 * This will run until the simulation either fails to find an exit, or the entities exit.
 	 * @returns true if the maze was successfuly solved. false otherwise.
	 */
	bool run();

private:
	// Game board that the bot will move through.
	Maze* m_pMaze;

	// Reference to the bot that will travel the maze
	Bot* m_pBot;

	// Location of the exit point on the maze
	Maze::tCoord m_ExitCoord;

	/**
	 * Initializes the maze cells with the state from the configuration file
	 * @param pMaze - pointer to the maze instance
	 * @param rows - List of rows to set the maze's state with.
 	 * @param dim - dimensions of the maze
	 */
	void initMazeCellsState(Maze* pMaze, EnvConfig::tMazeRows row, Maze::tDimension dim);

	/**
	 * Deletes any allocated memory used during run
	 */
	void cleanup();
};

#endif // !defined(_GAME_HPP_)