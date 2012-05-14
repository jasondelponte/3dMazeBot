#ifndef _ENV_CONFIG_HPP_
#define _ENV_CONFIG_HPP_

#include <vector>
#include <string>
#include <map>

#include "maze.hpp"


/**
 * Provides a method to convert the input maze definition file into
 * a usable format that the maze can be built with
 */
class EnvConfig {
public:
	// Defines a point of interest in the maze where the position
	// of it needs to be identified at the start.
	struct tCfgLoc {
		Maze::tCoord coord;
		int row;

		tCfgLoc(int r=0, Maze::tCoord c = Maze::tCoord()): row(r), coord(c){};
	};

	// A 2 dimentional list of the cells on the board layed out in rows
	typedef std::vector<Maze::eCell> tMazeRow;
	typedef std::vector<tMazeRow> tMazeRows;
	typedef std::map<char, tCfgLoc> tBotCfgLocs;
	typedef std::map<char, Maze::tCoord> tBotCoords;

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
	Maze::tDimension getDim() { return m_dim; };

	/**
	 * Returns the location of the bots' starting points in the maze
	 * @returns tBotCoords - Location of the bots' starting point in the meaze.
	 */
	tBotCoords getBotCoords();

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

	/**
	 * Calculates the Y and Z coordinates using the provided row and dimenions values
	 * @param x int - existing x coordinate value
	 * @param row int - defines which row the item is in
	 * @param dim tDimension - object specifing the maze's sizes.
	 * @returns coordinate of the cell in the maze
	 */
	static Maze::tCoord calcCoordFromRowDim(int x, int row, Maze::tDimension dim);

private:

	// Total number of layers
	Maze::tDimension m_dim;

	// Defines the bots' starting location in the maze
	tBotCfgLocs m_bots;

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
	tMazeRow parseRow(std::string line, int rowIdx);
};

#endif // !defined(_ENV_CONFIG_HPP_)
