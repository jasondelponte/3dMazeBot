#ifndef _TEST_UNIT_HPP_
#define _TEST_UNIT_HPP_

#include <stdlib.h>
#include <string>
#include <map>

class TestUnit {
public:
	/**
	 * Defines the object used to keep track of failure/success counts from each test.
	 */
	struct tTestResult {
		int count;
		int fails;
		int succs;

		tTestResult(int c=0, int f=0, int s=0): count(c), fails(f), succs(s) {};

		tTestResult & operator += (const tTestResult &res) {
			count += res.count;
			fails += res.fails;
			succs += res.succs;
			return *this;
		}
	};

	/**
	 * Construct the test unit object, and initialize it for use
	 */
	TestUnit();

	/**
	 * Runs all unit tests include in the array of tests
	 * the result of all the test will be returned
	 * @returns result of tests run
	 */
	virtual tTestResult runTests();

protected:
	struct tTestData {
		void* testObj;
		tTestData(void* o=NULL): testObj(o) {}
	};

	// Test function of the the children which will contain
	// the actuall tests to be run.
	typedef bool (*tTestFunc)(tTestData* pTestData);

	// Defines the type for a list of tests
	typedef std::map<std::string, tTestFunc> tTestList;

	// Keeps track of all results from the tests
	tTestResult m_results;

	// Vector containing the list of tests
	tTestList m_tests;

	/**
	 * Creates the test object container which can be used
	 * to hold the data between the before, runs, and after
	 * functions.  The TestUnit version of this method should
	 * be called before the child's method is executed.
	 * Not required though. 
	 * @returns tTestData container
	 */
	virtual tTestData* beforeEach();

	/**
	 * Will be run after each test has completed.  This method
	 * needs to be called after the child's version is called if there was one.
	 * @params pTestData tTestData - The container for test objects, if any used.
	 */
	virtual void afterEach(tTestData* pTestData);

};

#endif //!defined(_TEST_UNIT_HPP_)