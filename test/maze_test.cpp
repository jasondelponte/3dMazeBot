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
 * @returns true of succesful test, false otherwise.
 */
bool MazeTest::TestCreateMaze(TestUnit::tTestData* pTestData) {
	Maze::tDimension dim = Maze::tDimension(10, 5, 2);

	Maze* pMaze;
	pTestData->testObj = pMaze = new Maze(dim);

	// Make sure the elements are correct
	Maze::tGrid* grid = pMaze->getGrid();

	if (grid == NULL) {
		cerr << "Maze grid is not defined." << endl;
		return false;
	}

	if (grid->dim.width != 10 || grid->dim.height != 5 || grid->dim.depth != 2) {
		cerr << "Maze grid dimensions do not match those specified." << endl;
		return false;
	}

	if (grid->layout == NULL) {
		cerr << "Maze grid layout was not defined." << endl;
		return false;
	}

	for (int x=0; x < grid->dim.width; x++) {
		for (int y=0; y < grid->dim.height; y++) {
			for (int z=0; z < grid->dim.depth; z++) {
				Maze::tCell cell = grid->layout[x][y][z];
				if (cell.state != Maze::CELL_EMPTY || cell.coord.x != x || cell.coord.y != y || cell.coord.z != z) {
					cerr << "Maze grid layout not initialized correctly." << endl;
					return false;
				}
			}
		}
	}

	return true;
}

