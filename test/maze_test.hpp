#ifndef _MAZE_TEST_HPP_
#define _MAZE_TEST_HPP_

#include <string>

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
	 * @returns error string if there was an error
	 */
	static std::string TestCreateMaze(TestUnit::tTestData* pTestData);

	/**
	 * Verifies that cells in a grid can have their state set.
	 * @params pTestData - test object to store the maze in so it
	 * will get cleaned up in all cases.
	 * @returns error string if there was an error
	 */
	static std::string TestSetCellState(TestUnit::tTestData* pTestData);

	/**
	 * Verifies the coord validation logic works
	 * @params pTestData - test object to store the maze in so it
	 * will get cleaned up in all cases.
	 * @returns error string if there was an error
	 */
	static std::string TestCoordValidation(TestUnit::tTestData* pTestData);

	/**
	 * Create a new maze object before each test which is nitialized.
	 * @returns test data object container.
	 */
	TestUnit::tTestData* beforeEach();

	/**
	 * Clean up the temporary test maze objects created during
	 * each test
	 * @param pTestData test data container
	 */
	void afterEach(TestUnit::tTestData* pTestData);

};

#endif //!defined(_MAZE_TEST_HPP_)
