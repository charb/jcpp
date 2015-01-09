#include "NativeTestUtils.h"
#include "jcpp/native/api/NativeFactory.h"
#include "jcpp/native/api/NativeException.h"

#include <iostream>

#define TEST_NAME "Native System"

using namespace jcpp::native::api;

int main(int argc, char *argv[]) {
	logTitle(TEST_NAME);

	try {

		NativeSystem * system = NativeFactory::getNativeSystem();
		ASSERT_TRUE_EM(system, "Native System pointer returned from the Native Factory is null", TEST_NAME)

		jlong ctm = system->currentTimeMillis();
		logInfo("Current Time Millis = %lld\n", ctm);

		std::map<NativeString, NativeString> env;
		system->getEnv(env);

		logInfo("Environment Variables:");
		for (std::map<NativeString, NativeString>::iterator it = env.begin(); it != env.end(); ++it) {
			printf(">>> %s=", it->first.getString().c_str());
			std::string envValue = it->second.getString();
			const char * envValueStr = envValue.c_str();
			int length = envValue.length();
			int offset = 0;
			while (length > 0) {
				int printLength = length > 256 ? 256 : length;
				printf("%.*s", printLength, envValueStr + offset);
				offset += printLength;
				length -= printLength;
			}
			printf("\n");
		}

		logInfo("");
		NativeString value = system->getEnv("HOME");
		logInfo("Home env variable value = %s", value.getString().c_str());
		ASSERT_TRUE_M(!value.isEmpty(), "Testing getting a single env var value.", "Failed to get the env var value of HOME", TEST_NAME);

	} catch (NativeException& e) {
		logError("NativeException thrown Class = %s Method = %s Message = %s Error Code = %d", e.getClassName().getString().c_str(), e.getMethodName().getString().c_str(), e.getMessage().getString().c_str(), e.getErrorCode());
		FAIL_TEST(TEST_NAME)
	} catch (...) {
		logError("Exception thrown in Main Method !");
		FAIL_TEST(TEST_NAME)
	}

	PASS_TEST(TEST_NAME)
}
