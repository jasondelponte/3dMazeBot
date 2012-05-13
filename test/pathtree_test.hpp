#ifndef _PATHTREE_TEST_HPP_
#define _PATHTREE_TEST_HPP_

#include <string>

#include "test_unit.hpp"

class PathTreeTest : public TestUnit {
public:

	/**
	 * Initialize the test, and also make sure to initialize the 
	 * parent test unit as well.
	 */
	PathTreeTest();

private:

	/**
	 * Delete the path tree object if it is set
	 * @param pTestData container object of test data
	 */
	void afterEach(TestUnit::tTestData* pTestData);

	/**
	 * Verifies a path node can be compared to a maze cell
	 * @param pTestData - pointer to test container, not used for these tests
	 * @returns error string if any.
	 */
	static std::string TestCompareNodeToCell(TestUnit::tTestData* pTestData);


	/**
	 * Verify cells can be added to the path tree
	 * @param pTestData - pointer to test container, not used for these tests
	 * @returns error string if any.
	 */
	static std::string TestAddCellsToPathTree(TestUnit::tTestData* pTestData);

	/**
	 * Verify that the tree can search for ancestors from a leaf
	 * @param pTestData - pointer to test container, not used for these tests
	 * @returns error string if any.
	 */
	static std::string TestAncstorCellSearch(TestUnit::tTestData* pTestData);

};

#endif //!defined(_PATHTREE_TEST_HPP_)
