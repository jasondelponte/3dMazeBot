#include "env_config_test.hpp"
#include "env_config.hpp"
#include "maze.hpp"

#include <stdio.h>
#include <iostream>

using namespace std;

/**
 * Initialize the test, and also make sure to initialize the 
 * parent test unit as well.
 */
EnvConfigTest::EnvConfigTest(): TestUnit() {
	m_tests["EnvConfigTest::TestLoadProvidedFile"] = &TestLoadProvidedFile;
	m_tests["EnvConfigTest::TestCalcCoordFromRowDim"] = &TestCalcCoordFromRowDim;
}

/**
 * Loads a test file from disk, and verifieds it was loaded correctly
 * @param pTestData - pointer to test container, not used for these tests
 * @returns error string if any.
 */
string EnvConfigTest::TestLoadProvidedFile(TestUnit::tTestData* pTestData) {
	char errStr[100] = {0x00};

	EnvConfig cfg;
	char fileName[] = "test/configs/inputab";
	if (!cfg.parseEnv(fileName)) {
		return "Failed to load environment config file";
	}

	Maze::tDimension dim = cfg.getDim();
	if (dim.width != 5 || dim.height != 3 || dim.depth != 4) {
		sprintf(errStr, "%dx%dx%d", dim.width, dim.height, dim.depth);
		return "Invalid dimensions were read from file, expecting 5x3x4. Got: " + string(errStr);
	}

	EnvConfig::tBotCoords cords = cfg.getBotCoords();
	if (cords['A'] != Maze::tCoord(2,1,2)) {
		return "The location of the A bot is not valid, expecting (2,1,2). Got: " + cords['A'].String();
	}
	if (cords['B'] != Maze::tCoord(0,0,0)) {
		return "The location of the B bot is not valid, expecting (2,1,2). Got: " + cords['B'].String();
	}

	Maze::tCoord exitLoc = cfg.getExitCoord();
	if (exitLoc != Maze::tCoord(4,2,0)) {
		return "The location of the exit is not valid, expecting (4,2,0). Got: " + exitLoc.String();
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

/**
 * Verifies that the calculate coordinates from a row/dim works correctly
 * @param pTestData - pointer to test container, not used for these tests
 * @returns error string if any.
 */
std::string EnvConfigTest::TestCalcCoordFromRowDim(TestUnit::tTestData* pTestData) {
	char errStr[100] = {0x00};

	int x = 0;
	int row = 0;
	Maze::tDimension dim = Maze::tDimension(1, 1, 1);
	Maze::tCoord coord = EnvConfig::calcCoordFromRowDim(x, row, dim);
	Maze::tCoord expected = Maze::tCoord(0, 0, 0);
	if (coord != expected) {
		return "Failed to calculate coord, expected " + expected.String() + ". Got: " + coord.String();
	}

	x = 9;
	row = 99;
	dim = Maze::tDimension(10, 10, 10);
	coord = EnvConfig::calcCoordFromRowDim(x, row, dim);
	expected = Maze::tCoord(9, 9, 9);
	if (coord != expected) {
		return "Failed to calculate coord, expected " + expected.String() + ". Got: " + coord.String();
	}

	x = 1;
	row = 23;
	dim = Maze::tDimension(10, 10, 10);
	coord = EnvConfig::calcCoordFromRowDim(x, row, dim);
	expected = Maze::tCoord(1, 2, 3);
	if (coord != expected) {
		return "Failed to calculate coord, expected " + expected.String() + ". Got: " + coord.String();
	}

	x = 2;
	row = 0;
	dim = Maze::tDimension(5, 3, 4);
	coord = EnvConfig::calcCoordFromRowDim(x, row, dim);
	expected = Maze::tCoord(2, 0, 0);
	if (coord != expected) {
		return "Failed to calculate coord, expected " + expected.String() + ". Got: " + coord.String();
	}

	x = 2;
	row = 1;
	dim = Maze::tDimension(5, 3, 4);
	coord = EnvConfig::calcCoordFromRowDim(x, row, dim);
	expected = Maze::tCoord(2, 0, 1);
	if (coord != expected) {
		return "Failed to calculate coord, expected " + expected.String() + ". Got: " + coord.String();
	}

	x = 2;
	row = 2;
	dim = Maze::tDimension(5, 3, 4);
	coord = EnvConfig::calcCoordFromRowDim(x, row, dim);
	expected = Maze::tCoord(2, 0, 2);
	if (coord != expected) {
		return "Failed to calculate coord, expected " + expected.String() + ". Got: " + coord.String();
	}

	x = 2;
	row = 3;
	dim = Maze::tDimension(5, 3, 4);
	coord = EnvConfig::calcCoordFromRowDim(x, row, dim);
	expected = Maze::tCoord(2, 0, 3);
	if (coord != expected) {
		return "Failed to calculate coord, expected " + expected.String() + ". Got: " + coord.String();
	}

	x = 2;
	row = 4;
	dim = Maze::tDimension(5, 3, 4);
	coord = EnvConfig::calcCoordFromRowDim(x, row, dim);
	expected = Maze::tCoord(2, 1, 0);
	if (coord != expected) {
		return "Failed to calculate coord, expected " + expected.String() + ". Got: " + coord.String();
	}

	x = 2;
	row = 5;
	dim = Maze::tDimension(5, 3, 4);
	coord = EnvConfig::calcCoordFromRowDim(x, row, dim);
	expected = Maze::tCoord(2, 1, 1);
	if (coord != expected) {
		return "Failed to calculate coord, expected " + expected.String() + ". Got: " + coord.String();
	}

	x = 2;
	row = 6;
	dim = Maze::tDimension(5, 3, 4);
	coord = EnvConfig::calcCoordFromRowDim(x, row, dim);
	expected = Maze::tCoord(2, 1, 2);
	if (coord != expected) {
		return "Failed to calculate coord, expected " + expected.String() + ". Got: " + coord.String();
	}

	x = 2;
	row = 7;
	dim = Maze::tDimension(5, 3, 4);
	coord = EnvConfig::calcCoordFromRowDim(x, row, dim);
	expected = Maze::tCoord(2, 1, 3);
	if (coord != expected) {
		return "Failed to calculate coord, expected " + expected.String() + ". Got: " + coord.String();
	}

	x = 2;
	row = 8;
	dim = Maze::tDimension(5, 3, 4);
	coord = EnvConfig::calcCoordFromRowDim(x, row, dim);
	expected = Maze::tCoord(2, 2, 0);
	if (coord != expected) {
		return "Failed to calculate coord, expected " + expected.String() + ". Got: " + coord.String();
	}

	x = 2;
	row = 9;
	dim = Maze::tDimension(5, 3, 4);
	coord = EnvConfig::calcCoordFromRowDim(x, row, dim);
	expected = Maze::tCoord(2, 2, 1);
	if (coord != expected) {
		return "Failed to calculate coord, expected " + expected.String() + ". Got: " + coord.String();
	}

	x = 2;
	row = 10;
	dim = Maze::tDimension(5, 3, 4);
	coord = EnvConfig::calcCoordFromRowDim(x, row, dim);
	expected = Maze::tCoord(2, 2, 2);
	if (coord != expected) {
		return "Failed to calculate coord, expected " + expected.String() + ". Got: " + coord.String();
	}

	x = 2;
	row = 11;
	dim = Maze::tDimension(5, 3, 4);
	coord = EnvConfig::calcCoordFromRowDim(x, row, dim);
	expected = Maze::tCoord(2, 2, 3);
	if (coord != expected) {
		return "Failed to calculate coord, expected " + expected.String() + ". Got: " + coord.String();
	}

	return "";
}
