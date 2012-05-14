#ifndef _PATHFIND_TEST_HPP
#define _PATHFIND_TEST_HPP

#include "test_unit.hpp"
#include "game.hpp"
#include "maze.hpp"

class PathFindTest : public TestUnit {
public:
	/**
	 * Initialize the test, and also make sure to initialize the 
	 * parent test unit as well.
	 */
	PathFindTest();
private:
	struct tTestCont {
		Game game;
		Maze* pMaze;
		tTestCont(Game g=Game(), Maze* m=NULL): game(g), pMaze(m) {}
	};

	/**
	 * Initialize the test unit with an environment
	 * @returns test environment container
	 */
	TestUnit::tTestData* beforeEach();

	/**
	 * Delete the allocated objects if there were any
	 * @param pTestData container object of test data
	 */
	void afterEach(TestUnit::tTestData* pTestData);

	/**
	 * Verifies a grid can be loaded, and a path tree generated from it.
	 * @param pTestData - pointer to test container, not used for these tests
	 * @returns error string if any.
	 */
	static std::string TestGeneratePathTreeFromGrid(TestUnit::tTestData* pTestData);
};

#endif //!defined(_PATHFIND_TEST_HPP)
