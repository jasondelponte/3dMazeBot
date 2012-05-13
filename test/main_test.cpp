#include <stdio.h>
#include <stdlib.h>

#include "test_unit.hpp"
#include "maze_test.hpp"
#include "env_config_test.hpp"
#include "pathtree_test.hpp"

/**
 * Run through all of the test case and report failure for any testcase that fails
 */
int main(int argc, char* argv[]) {
	// Build a list of the tests
	TestUnit *tests[] = {
		new MazeTest(),
		new EnvConfigTest(),
		new PathTreeTest()
	};
	int numTests = sizeof(tests)/sizeof(TestUnit*);


	// Run each test in succession gathering the results after each is run
	TestUnit::tTestResult results;
	for (int idx=0; idx < numTests; idx++) {
		results += tests[idx]->runTests();

		// clean up each test after we are done with it
		delete tests[idx];
	}


	printf("Finished %d tests, %d failed, %d succesful.\n",
		results.count, results.fails, results.succs);
	// We should exit with a failure status if any of the tests failed.
	if (results.fails != 0) {
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
