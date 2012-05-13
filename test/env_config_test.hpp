#ifndef _ENV_CONFIG_TEST_HPP_
#define _ENV_CONFIG_TEST_HPP_

#include <string>

#include "test_unit.hpp"

class EnvConfigTest : public TestUnit {
public:

	/**
	 * Initialize the environment ocnfig test, and also make sure to initialize the 
	 * parent test unit as well.
	 */
	EnvConfigTest();

private:

	/**
	 * Loads a test file from disk, and verifieds it was loaded correctly
	 * @param pTestData - pointer to test container, not used for these tests
	 * @returns error string if any.
	 */
	static std::string TestLoadProvidedFile(TestUnit::tTestData* pTestData);

};

#endif //!defined(_ENV_CONFIG_TEST_HPP_)