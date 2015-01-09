#include "NativeTestUtils.h"
#include "jcpp/native/api/NativeAPI.h"

#define TEST_NAME "Native API"

bool testPrimitiveSize(char * name, int size, int expectedSize) {
	if (size != expectedSize) {
		logError("Invalid sizeof \"%s\" = %d. Size should be %d", name, size, expectedSize);
		return false;
	} else {
		logInfo("Valid sizeof \"%s\" = %d", name, size);
		return true;
	}
}

int main(int argc, char *argv[]) {
	logTitle(TEST_NAME);

	logInfo("Testing primitive type sizes ...");

	if (!testPrimitiveSize("jint", sizeof(jint), 4)) {
		FAIL_TEST(TEST_NAME);
	}
	if (!testPrimitiveSize("jshort", sizeof(jshort), 2)) {
		FAIL_TEST(TEST_NAME);
	}
	if (!testPrimitiveSize("jlong", sizeof(jlong), 8)) {
		FAIL_TEST(TEST_NAME);
	}
	if (!testPrimitiveSize("jbyte", sizeof(jbyte), 1)) {
		FAIL_TEST(TEST_NAME);
	}
	if (!testPrimitiveSize("jfloat", sizeof(jfloat), 4)) {
		FAIL_TEST(TEST_NAME);
	}
	if (!testPrimitiveSize("jdouble", sizeof(jdouble), 8)) {
		FAIL_TEST(TEST_NAME);
	}
	if (!testPrimitiveSize("jchar", sizeof(jchar), 2)) {
		FAIL_TEST(TEST_NAME);
	}

	jint maxjint = JINT_MAX;
	ASSERT_TRUE_M(maxjint > 0, "Tested Max jint is positive", "Max jint is not positive", TEST_NAME)
	ASSERT_M(maxjint, JINT_MAX, "Tested Max jint value", "Max jint is not settable", TEST_NAME)
	maxjint += 1;
	ASSERT_TRUE_M(maxjint < 0, "Tested Max jint is negative after adding 1", "Max jint is still positive after adding one", TEST_NAME)

	jint minjint = JINT_MIN;
	ASSERT_TRUE_M(minjint < 0, "Tested Min jint is negative", "Min jint is not negative", TEST_NAME)
	ASSERT_M(minjint, JINT_MIN, "Tested Min jint value", "Min jint is not settable", TEST_NAME)
	minjint -= 1;
	ASSERT_TRUE_M(minjint > 0, "Tested Min jint is positive after subtracting 1", "Min jint is still negative after adding one", TEST_NAME)

	// TODO add tests for other primitives;

	PASS_TEST(TEST_NAME)

}

