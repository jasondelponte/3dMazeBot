#include "pathfind_test.hpp"

#include <stdio.h>
#include <iostream>

using namespace std;


/**
 * Initialize the test, and also make sure to initialize the 
 * parent test unit as well.
 */
PathFindTest::PathFindTest(): TestUnit() {
	m_tests["PathFindTest::TestGeneratePathTreeFromGrid"] = &TestGeneratePathTreeFromGrid;
}

/**
 * Initialize the test unit with an environment
 * @returns test environment container
 */
TestUnit::tTestData* PathFindTest::beforeEach() {
	TestUnit::tTestData* pTestData = TestUnit::beforeEach();
	tTestCont* pCont = new tTestCont();

	// Parses the input file and builds sets up the environment so 
	// the game maze can be built.
	EnvConfig cfg;
	char fileName[] = "test/configs/input00";
	if (!cfg.parseEnv(fileName)) {
		cerr << "Failed to load environment config file" << endl;
		return pTestData;
	}
	// We need to build the environment for the game.  This includes
	// placing the bot, and building the maze and exit.
	pCont->game.buildEnv(cfg);
	pCont->pMaze = pCont->game.getMaze();

	pTestData->testObj = pCont;
	return pTestData;
}

/**
 * Delete the allocated objects if there were any
 * @param pTestData container object of test data
 */
void PathFindTest::afterEach(TestUnit::tTestData* pTestData) {
	if (pTestData->testObj != NULL) {
		delete (tTestCont*)pTestData->testObj;
		pTestData->testObj = NULL;
	}

	TestUnit::afterEach(pTestData);
}

/**
 * Verifies a grid can be loaded, and a path tree generated from it.
 * @param pTestData - pointer to test container, not used for these tests
 * @returns error string if any.
 */
string PathFindTest::TestGeneratePathTreeFromGrid(TestUnit::tTestData* pTestData) {
	char errStr[100] = {0x00};

	tTestCont* pCont = (tTestCont*)pTestData->testObj;
	if (pCont == NULL || pCont->pMaze == NULL) { return "Test data not loaded."; }
	Maze* pMaze = pCont->pMaze;

	PathFind pathfinder;
	pathfinder.setGrid(pMaze->getGrid());

	pathfinder.setLoc(Maze::tCoord(0,0,0));
	Maze::tCoord destCoord = Maze::tCoord(0,0,1);
	PathFind::tRoute route = pathfinder.findRoute(destCoord);
	if (route.size() != 1 && route.top()->coord == destCoord) {
		return "Failed to find route to cell directly south of starting point";
	}

	pathfinder.setLoc(Maze::tCoord(0,0,0));
	destCoord = Maze::tCoord(2,1,2);
	route = pathfinder.findRoute(destCoord);
	if (route.size() != 15) {
		sprintf(errStr, "%d", (int)route.size());
		return "Failed to find route dest at " + destCoord.String();
	}

	return "";
}
