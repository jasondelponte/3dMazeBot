#ifndef _ENV_CONFIG_HPP_
#define _ENV_CONFIG_HPP_

#include <vector>
#include <string>

#include "maze.hpp"


/**
 * Provides a method to convert the input maze definition file into
 * a usable format that the maze can be built with
 */
class EnvConfig {
public:
	// A 2 dimentional list of the cells on the board layed out in rows
	typedef std::vector<std::vector<Maze::eCell > > tMazeRows;

	/**
	 * Builds the game environment from the config file
	 * @param envFileName char[] - Config file defining the maze row by row
	 * @returns true if the environment was successfully loaded, false otherwise
	 */
	bool parseEnv(char cfgFileName[]);

	/**
	 * Returns the dimentions of the maze
	 * @returns tDimension - Contains the height, width, depth of the maze
	 */
	Maze::tDimension getDimensions() { return m_dim; };

	/**
	 * Returns the location of the bot's starting point in the maze
	 * @returns tCoord - Location of the bot's starting point in the meaze.
	 */
	Maze::tCoord getBotCoord() { return m_botLoc.coord; };

	/**
	 * Returns the coordinates of the exit in the maze
	 * @returns tCoord - Location of the exit in the maze
	 */
	Maze::tCoord getExitCoord() { return m_exitLoc.coord; };

	/**
	 * Returns a the cells in a maze aligned in rows
	 * @returns tMazeRows - List of rows containing list of cells
	 */
	tMazeRows getMazeRows() { return m_rows; };


private:
	// Defines a point of interest in the maze where the position
	// of it needs to be identified at the start.
	struct tCfgLoc {
		Maze::tCoord coord;
		int row;

		tCfgLoc(int r=0, Maze::tCoord c = Maze::tCoord()): row(r), coord(c){};
	};

	// Total number of layers
	Maze::tDimension m_dim;

	// Defines the bot's starting location in the maze
	tCfgLoc m_botLoc;

	// Defines the exit's location in the maze
	tCfgLoc m_exitLoc;

	// Contains a list of cells separated into rows
	tMazeRows m_rows;

	/**
	 * Reads the line character by character building a row of eCells.
	 * If the bot or exist is found the class's config loc will be updated
	 * with its X position and row.  Which can be used later to calculate
	 * the Y and Z position. If an unknown cell is found it will be substituted with
 	 * an empty cell.
	 * @param line string - input string which will be parsed and turned into cells.
 	 * @param rowIdx int - The index of the row being parsed.
	 * @returns vector of cells representing the empty/solid state of the row cells.
	 */
	std::vector<Maze::eCell> parseRow(std::string line, int rowIdx);

	/**
	 * Updates the passed in config loc's Y and Z coords using the existing
	 * row value, and the passed in dimensions.
	 * @param loc tCfgLoc - Object which needs the y and z coords updated
	 * @param dim tDimension - object specifing the maze's sizes.
	 */
	void updateCfgLocYZ(tCfgLoc &loc, Maze::tDimension dim);
};

#endif // !defined(_ENV_CONFIG_HPP_)
