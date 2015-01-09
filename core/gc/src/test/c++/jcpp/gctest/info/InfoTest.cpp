#include "NativeTestUtils.h"

#include "jcpp/gctest/info/SampleThreadInfo.h"

#include <stdio.h>

#define TEST_NAME "Info"

using namespace jcpp::gctest::info;

//~-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//~ Main Method
//~-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main(int argc, char *argv[]) {
	logTitle(TEST_NAME);

	try {

		SampleThreadInfo* thread = new SampleThreadInfo();
		thread->run();

	} catch (...) {
		logError("Exception thrown in Main Method !");
		FAIL_TEST(TEST_NAME)
	}

	PASS_TEST(TEST_NAME)
}
