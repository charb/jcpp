#include "NativeTestUtils.h"
#include "jcpp/native/api/NativeFactory.h"

using namespace jcpp::native::api;

#define TEST_NAME "Native Factory"

int main(int argc, char *argv[]) {

	logTitle(TEST_NAME);

	ASSERT_TRUE_M(NativeFactory::getNativeSystem(), "Tested getting Native System Instance", "Native System Instance returned from Native Factory was null", TEST_NAME);

	ASSERT_TRUE_M(NativeFactory::getNativeFileFactory(), "Tested getting Native File Factory Instance", "Native File Factory Instance returned from Native Factory was null", TEST_NAME);

	ASSERT_TRUE_M(NativeFactory::getNativeThreadFactory(), "Tested getting Native Thread Factory Instance", "Native Thread Factory Instance returned from Native Factory was null", TEST_NAME);

	ASSERT_TRUE_M(NativeFactory::getNativeIOFactory(), "Tested getting Native IO Factory Instance", "Native IO Factory Instance returned from Native Factory was null", TEST_NAME);

	ASSERT_TRUE_M(NativeFactory::getNativeNetFactory(), "Tested getting Native Net Factory Instance", "Native Net Factory Instance returned from Native Factory was null", TEST_NAME);

	PASS_TEST(TEST_NAME)
}
