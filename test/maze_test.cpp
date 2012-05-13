#include "maze_test.hpp"
#include "maze.hpp"

#include <stdio.h>
#include <iostream>

using namespace std;

/**
 * Initialize the maze test, and also make sure to initialize the 
 * parent test unit as well.
 */
MazeTest::MazeTest(): TestUnit() {
	m_tests["TestCreateMaze"] = &TestCreateMaze;
	m_tests["TestSetCellState"] = &TestSetCellState;
	m_tests["TestCoordValidation"] = &TestCoordValidation;
}

/**
 * Create a new maze object before each test which is nitialized.
 * @returns test data object container.
 */
TestUnit::tTestData* MazeTest::beforeEach() {
	TestUnit::tTestData* pTestData = TestUnit::beforeEach();

	Maze::tDimension dim = Maze::tDimension(10, 5, 7);
	pTestData->testObj = new Maze(dim);

	return pTestData;
}

/**
 * Clean up the temporary test maze objects created during
 * each test
 * @param pTestData test data container
 */
void MazeTest::afterEach(TestUnit::tTestData* pTestData) {
	if (pTestData->testObj != NULL) {
		delete (Maze*)pTestData->testObj;
	}

	TestUnit::afterEach(pTestData);
}

/**
 * Verify that the maze can be created with a specific size
 * @params pTestData - test object to store the maze in so it
 * will get cleaned up in all cases.
 * @returns error string if there was an error
 */
string MazeTest::TestCreateMaze(TestUnit::tTestData* pTestData) {
	Maze* pMaze = (Maze*)pTestData->testObj;

	// Get the grid so we can verify it
	Maze::tGrid* grid = pMaze->getGrid();

	// The grid was created
	if (grid == NULL) {
		return "Maze grid is not defined.";
	}

	// the dimensions were set.
	if (grid->dim.width != 10 || grid->dim.height != 5 || grid->dim.depth != 7) {
		return "Maze grid dimensions do not match those specified.";
	}

	// They layout pointer is set
	if (grid->layout == NULL) {
		return "Maze grid layout was not defined.";
	}

	// All cells were intitlized to empty, and with their correct coords
	for (int x=0; x < grid->dim.width; x++) {
		for (int y=0; y < grid->dim.height; y++) {
			for (int z=0; z < grid->dim.depth; z++) {
				Maze::tCell cell = grid->layout[x][y][z];
				if (cell.state != Maze::CELL_EMPTY || cell.coord.x != x || cell.coord.y != y || cell.coord.z != z) {
					return "Maze grid layout not initialized correctly.";
				}
			}
		}
	}

	return "";
}

/**
 * Verifies that cells in a grid can have their state set.
 * @params pTestData - test object to store the maze in so it
 * will get cleaned up in all cases.
 * @returns error string if there was an error
 */
string MazeTest::TestSetCellState(TestUnit::tTestData* pTestData) {
	Maze* pMaze = (Maze*)pTestData->testObj;

	Maze::tCoord chg1 = Maze::tCoord(0, 0, 0);
	Maze::tCoord chg2 = Maze::tCoord(5, 3, 1); 
	Maze::tCoord chg3 = Maze::tCoord(9, 4, 6);
	Maze::tCoord noChg = Maze::tCoord(2, 2, 2);

	// Update the cells, start, end, and inner item
	pMaze->updateCell(chg1, Maze::CELL_SOLID);
	pMaze->updateCell(chg2, Maze::CELL_OCCUPIED);
	pMaze->updateCell(chg3, Maze::CELL_EXIT);

	Maze::tGrid* pGrid = pMaze->getGrid();

	// Verify the changes only occred where desired
	Maze::tCell cell = pGrid->layout[noChg.x][noChg.y][noChg.z];
	if (cell.state != Maze::CELL_EMPTY) {
		return "Cell state change when it wasn't supposed to.";
	}

	// Verify changes
	cell = pGrid->layout[chg1.x][chg1.y][chg1.z];
	if (cell.state != Maze::CELL_SOLID) {
		return "Unable to set cell to solid state.";
	}
	cell = pGrid->layout[chg2.x][chg2.y][chg2.z];
	if (cell.state != Maze::CELL_OCCUPIED) {
		return "Unable to set cell to occupied state.";
	}
	cell = pGrid->layout[chg3.x][chg3.y][chg3.z];
	if (cell.state != Maze::CELL_EXIT) {
		return "Unable to set cell to exit state.";
	}

	return "";
}

/**
 * Verifies the coord validation logic works
 * @params pTestData - test object to store the maze in so it
 * will get cleaned up in all cases.
 * @returns error string if there was an error
 */
string MazeTest::TestCoordValidation(TestUnit::tTestData* pTestData) {
	Maze* pMaze = (Maze*)pTestData->testObj;

	if (pMaze->isValidCoord(Maze::tCoord(-1, 0, 0))) {
		return "Failed to mark coord(-1, 0, 0) as invalid";
	}
	if (pMaze->isValidCoord(Maze::tCoord(0, -1, 0))) {
		return "Failed to mark coord(0, -1, 0) as invalid";
	}
	if (pMaze->isValidCoord(Maze::tCoord(0, 0, -1))) {
		return "Failed to mark coord(0, 0, -1) as invalid";
	}
	if (pMaze->isValidCoord(Maze::tCoord(100, 0, 0))) {
		return "Failed to mark coord(100, 0, 0) as invalid";
	}
	if (pMaze->isValidCoord(Maze::tCoord(0, 100, 0))) {
		return "Failed to mark coord(0, 100, 0) as invalid";
	}
	if (pMaze->isValidCoord(Maze::tCoord(0, 0, 100))) {
		return "Failed to mark coord(0, 0, 100) as invalid";
	}

	return "";
}
