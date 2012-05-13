#include "env_config_test.hpp"
#include "env_config.hpp"

#include <stdio.h>
#include <iostream>

using namespace std;

/**
 * Initialize the maze test, and also make sure to initialize the 
 * parent test unit as well.
 */
EnvConfigTest::EnvConfigTest(): TestUnit() {
	m_tests["TestLoadProvidedFile"] = &TestLoadProvidedFile;
}


/**
 * Loads a test file from disk, and verifieds it was loaded correctly
 * @param pTestData - pointer to test container, not used for these tests
 * @returns error string if any.
 */
string EnvConfigTest::TestLoadProvidedFile(TestUnit::tTestData* pTestData) {
	char errStr[100] = {0x00};

	EnvConfig cfg;
	char fileName[] = "test/configs/input";
	if (!cfg.parseEnv(fileName)) {
		return "Failed to load environment config file";
	}

	Maze::tDimension dim = cfg.getDim();
	if (dim.width != 5 || dim.height != 3 || dim.depth != 4) {
		sprintf(errStr, "%dx%dx%d", dim.width, dim.height, dim.depth);
		return "Invalid dimensions were read from file, expecting 5x3x4. Got: " + string(errStr);
	}

	Maze::tCoord botLoc = cfg.getBotCoord();
	if (botLoc.x != 0 || botLoc.y != 0 || botLoc.z != 0) {
		sprintf(errStr, "%d,%d,%d", botLoc.x, botLoc.y, botLoc.z);
		return "The location of the bot is not valid, expecting (0,0,0). Got: " + string(errStr);
	}

	Maze::tCoord exitLoc = cfg.getExitCoord();
	if (exitLoc.x != 4 || exitLoc.y != 2 || exitLoc.z != 0) {
		sprintf(errStr, "%d,%d,%d", exitLoc.x, exitLoc.y, exitLoc.z);
		return "The location of the exit is not valid, expecting (4,2,0). Got: " + string(errStr);
	}

	EnvConfig::tMazeRows rows = cfg.getMazeRows();
	if (rows.size() != dim.height * dim.depth) {
		return "Invalid number of rows parsed, expecting 12";
	}

	EnvConfig::tMazeRows::const_iterator cIt;
	for (cIt = rows.begin(); cIt != rows.end(); cIt++) {
		EnvConfig::tMazeRow row = *cIt;
		if (row.size() != dim.width) {
			return "Length of parsed row does not match maze width dimensions";
		}
	}

	return "";
}
