#include "test_unit.hpp"

#include <iostream>

using namespace std;

/**
 * Construct the test unit object, and initialize it for use
 */
TestUnit::TestUnit(): m_results(tTestResult()) {}

/**
 * Creates the test object container which can be used
 * to hold the data between the before, runs, and after
 * functions.  The TestUnit version of this method should
 * be called before the child's method is executed.
 * Not required though. 
 * @returns tTestData container
 */
TestUnit::tTestData* TestUnit::beforeEach() {
	return new tTestData();
}

/**
 * Runs all unit tests include in the array of tests
 * the result of all the test will be returned
 * @returns result of tests run
 */
TestUnit::tTestResult TestUnit::runTests() {
	tTestResult results;
	results.count = m_tests.size();

	tTestList::const_iterator cIt;
	for (cIt = m_tests.begin(); cIt != m_tests.end(); cIt++) {
		string testName = (*cIt).first;
		tTestFunc test = (*cIt).second;

		// Create the testing environment
		tTestData* pTestData = beforeEach();

		// Run the test and keep track of failure/success
		bool testRes = false;

		try {
			testRes = test(pTestData);
		} catch (...) {
			cerr << testName << ", ERROR, unhandled exception." << endl;
		}

		if (testRes) {
			results.succs++;
		} else {
			cerr << testName << ", FAILED" << endl;
			results.fails++;
		}

		// Destory the testing environemnt
		afterEach(pTestData);
	}

	return results;
}

/**
 * Will be run after each test has completed.  This method
 * needs to be called after the child's version is called if there was one.
 * @params pTestData tTestData - The container for test objects, if any used.
 */
void TestUnit::afterEach(TestUnit::tTestData* pTestData) {
	if (pTestData != NULL) {
		delete pTestData;
	}
}
