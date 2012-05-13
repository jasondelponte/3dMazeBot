#ifndef _MAZE_TEST_HPP_
#define _MAZE_TEST_HPP_

#include "test_unit.hpp"

class MazeTest : public TestUnit {
public:

	/**
	 * Initialize the maze test, and also make sure to initialize the 
	 * parent test unit as well.
	 */
	MazeTest();

private:

	/**
	 * Verify that the maze can be created with a specific size
	 * @params pTestData - test object to store the maze in so it
	 * will get cleaned up in all cases.
	 * @returns true of succesful test, false otherwise.
	 */
	static bool TestCreateMaze(TestUnit::tTestData* pTestData);

	/**
	 * Clean up the temporary test maze objects created during
	 * each test
	 * @param pTestData test data container
	 */
	void afterEach(TestUnit::tTestData* pTestData);
};

#endif //!defined(_MAZE_TEST_HPP_)