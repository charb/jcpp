#include "NativeTestUtils.h"
#include "jcpp/native/api/NativeFactory.h"
#include "jcpp/native/api/NativeException.h"
#include "jcpp/native/api/nthread/NativeThread.h"
#include "jcpp/native/api/nthread/NativeStackTraceElement.h"
#include <vector>
#include <iostream>

#define TEST_NAME "Native Stack Trace"

using namespace jcpp::native::api;



void myMethod(int numCalls,NativeThread *&currentThread, std::vector<NativeStackTraceElement> &stackTrace){
	if (numCalls<=0){
		currentThread->getStackTrace(stackTrace);
		return;
	}

	myMethod(numCalls-1,currentThread, stackTrace);
	return;
}

int main(int argc, char **argv)
{
	logTitle(TEST_NAME);

	try{

		NativeSystem * system = NativeFactory::getNativeSystem();
		NativeThreadFactory * threadFactory = NativeFactory::getNativeThreadFactory();
		NativeThread * currentThread = threadFactory->currentThread();

		std::vector<NativeStackTraceElement> stackTrace;
		myMethod(10,currentThread, stackTrace);

		printf("Number of stack frames: %lu", stackTrace.size());

		for (int i=0; i<stackTrace.size(); i++){
			printf("\nStack Frame #%i\n", i);
			printf("File Name: %s\n", stackTrace[i].getFileName().getString().c_str());
			printf("Method Name: %s\n", stackTrace[i].getMethodName().getString().c_str());
			printf("Line Number: %i\n", stackTrace[i].getLineNumber());
		}


	}catch(NativeException &e){
		logError("NativeException thrown Class = %s Method = %s Message = %s Error Code = %d", e.getClassName().getString().c_str(), e.getMethodName().getString().c_str(), e.getMessage().getString().c_str(), e.getErrorCode());
		FAIL_TEST(TEST_NAME)
	} catch (...) {
		logError("Exception thrown in Main Method !");
		FAIL_TEST(TEST_NAME)
	}

	PASS_TEST(TEST_NAME);
}
