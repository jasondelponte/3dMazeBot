#include "env_config.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

using namespace std;


/**
 * Builds the game environment from the config file
 * @param envFileName char[] - Config file defining the maze row by row
 * @returns true if the environment was successfully loaded, false otherwise
 */
bool EnvConfig::parseEnv(char cfgFileName[]) {
	string line;

	// Open the config file and load each line defining our 
	ifstream cfg(cfgFileName);
	if (!cfg.is_open()) {
		return false;
	}

	// First line contains the number of layers
	if (!getline(cfg, line)) {
		cfg.close();
		return false;
	}
	m_dim.height = atoi(line.c_str());

	// Loop over the rest of the file to gather the layout
	// of the maze, the position of the bot, and the exit.
	while (getline(cfg, line)){
		// Get the width that we expect all rows to be
		if (m_dim.width == 0) {
			m_dim.width = line.size();
		} else if (m_dim.width != line.size()) {
			// The next row didn't match the width of the previous.
			// This is a fatal error because of an invalid input file.
			cfg.close();
			return false;
		}

		// Parse the line searching for solid or empty walls, bot, and exit.
		m_rows.push_back(parseRow(line, m_rows.size()));
	}
	cfg.close();

	// Make sure the input we got is correct, and the number
	// of rows equally divizes by the number of layers. This
	// must be a round number or there is an error in the input file.
	int numRows = m_rows.size();
	if (!(m_dim.height % numRows)) {
		return false;
	}
	m_dim.depth = numRows / m_dim.height;

	// Update the Bot and exit with their y & z coords based on their row.
	updateCfgLocYZ(m_botLoc, m_dim);
	updateCfgLocYZ(m_exitLoc, m_dim);

	return true;
}

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
vector<eCell> EnvConfig::parseRow(string line, int rowIdx) {
	const char * lineChar = line.c_str();
	int rowWidth = line.size();
	vector<eCell> row;

	for (int idx; idx < rowWidth; idx++) {
		switch (lineChar[idx]) {
			case '#': // Solid Cell
				row.push_back(CELL_SOLID);
			break;

			case '.': // Empty Cell
				row.push_back(CELL_EMPTY);
			break;

			case 'B': // The bot's location
				m_botLoc.coord.x = idx;
				m_botLoc.row = rowIdx;
				row.push_back(CELL_OCCUPIED);
			break;

			case 'E': // The exit's location
				m_exitLoc.coord.x = idx;
				m_exitLoc.row = rowIdx;
				row.push_back(CELL_EMPTY);
			break;

			default: // Unknown cell found!
				row.push_back(CELL_EMPTY);
				cerr << "Invalid character [" << lineChar[idx] << "] found at row: " <<
						rowIdx << ", col: " << idx <<". Substituting with empty." << endl;
			break;
		}
	}

	return row;
}

/**
 * Updates the passed in config loc's Y and Z coords using the existing
 * row value, and the passed in dimensions.
 * @param loc tCfgLoc - Object which needs the y and z coords updated
 * @param dim tDimension - object specifing the maze's sizes.
 */
void EnvConfig::updateCfgLocYZ(tCfgLoc &loc, tDimension dim) {
	loc.coord.y = loc.row % dim.depth;
	// Reduce Z by one to account for zero base instead of 1 coords.
	loc.coord.z = (dim.height / loc.row) - 1;
}
