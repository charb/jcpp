#include "NativeTestUtils.h"
#include "jcpp/native/api/NativeFactory.h"
#include "jcpp/native/api/NativeException.h"

#include "echo.h"

#include <iostream>

#define TEST_NAME "Native Library"

using namespace jcpp::native::api;
using namespace jcpp::native::api::library;

//~-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//~ DLL Exported Methods
//~-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

typedef char* (*EchoMethod)(char *);

//~-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//~ Main Method
//~-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main(int argc, char *argv[]) {
	logTitle(TEST_NAME);

	try {
		NativeLibraryFactory* libraryFactory = NativeFactory::getNativeLibraryFactory();

#if	defined (WIN32)
		NativeString libpath("..\\..\\..\\src\\test\\resources\\library\\x86-Windows-msvc\\echo-1.0.dll");

		NativeLibrary * echoLibrary = libraryFactory->createNativeLibrary(libpath);
		ASSERT_TRUE_M(echoLibrary, "Successfully loaded a Dynamic Library file", "Failed to load the dynamic library", TEST_NAME)

		NativeString methodName("echo");
		EchoMethod echoMethod =  (EchoMethod)echoLibrary->getFunction(methodName);

		ASSERT_TRUE_M(echoMethod, "Successfully got a function from the Dynamically loaded library", "Failed to get a function from the dynamically loaded library", TEST_NAME)

		char* s = "echo";
		char* r = echoMethod(s);

		ASSERT_M(s, r, "Successfully called the exported method", "Failed to call the exported method", TEST_NAME)

#endif

	} catch (NativeException& e) {
		logError("NativeException thrown Class = %s Method = %s Message = %s Error Code = %d", e.getClassName().getString().c_str(), e.getMethodName().getString().c_str(), e.getMessage().getString().c_str(), e.getErrorCode());
		FAIL_TEST(TEST_NAME)
	} catch (...) {
		logError("Exception thrown in Main Method !");
		FAIL_TEST(TEST_NAME)
	}

	PASS_TEST(TEST_NAME)
}
