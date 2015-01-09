#include "NativeTestUtils.h"
#include "jcpp/native/api/NativeFactory.h"
#include "jcpp/native/api/NativeException.h"

#include <iostream>

#define TEST_NAME "Native Process"

using namespace jcpp::native::api;
using namespace jcpp::native::api::io;
using namespace jcpp::native::api::process;

//~-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//~ Main Method
//~-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main(int argc, char *argv[]) {
	logTitle(TEST_NAME);

	try {

		NativeProcessFactory * processFactory = NativeFactory::getNativeProcessFactory();
		NativeProcess * localProcess = processFactory->getLocalProcess();

		ASSERT_TRUE_M(localProcess, "Successfully got the Local Process from the Native Process Factory", "Failed to get the Local Process from the Native Process Factory", TEST_NAME)

		logInfo("");
		logInfo("Getting local process pid...");
		NativeString localProcessPid = localProcess->getPid();
		logInfo("Local process pid = %s", localProcessPid.getString().c_str());

		logInfo("");
		logInfo("Getting local process command line...");
		NativeString localProcessCmd = localProcess->getCmd();
		logInfo("Local process command line = %s", localProcessCmd.getString().c_str());

		logInfo("");
		logInfo("Getting local process workdir...");
		NativeString localProcessWorkDir = localProcess->getWorkingDirectory();
		logInfo("Local process workdir = %s", localProcessWorkDir.getString().c_str());

		logInfo("");
		logInfo("Getting local process owner...");
		NativeString localProcessOwner = localProcess->getOwner();
		logInfo("Local process owner = %s", localProcessOwner.getString().c_str());

		logInfo("");
		logInfo("Getting local process tree...");
		std::vector<NativeString> localProcessTree;
		localProcess->getProcessTree(localProcessTree);
		logInfo("Local process tree depth = %d", localProcessTree.size());
		int localProcessParentIndex = 0;
		for (std::vector<NativeString>::iterator it = localProcessTree.begin(); it != localProcessTree.end(); it++) {
			logInfo("Process parent #%d pid = %s", ++localProcessParentIndex, (*it).getString().c_str());
		}

		logInfo("");
		logInfo("Getting local process environment variables...");
		std::map<NativeString, NativeString> localProcessEnv;
		localProcess->getEnvironment(localProcessEnv);
		logInfo("Local process environment variables:");
		for (std::map<NativeString, NativeString>::iterator it = localProcessEnv.begin(); it != localProcessEnv.end(); ++it) {
			printf(">>> %s=", it->first.getString().c_str());
			std::string envValue = it->second.getString();
			const char * envValueStr = envValue.c_str();
			int length = it->second.length();
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
		logInfo("Getting local process start date (millis since epoc)...");
		jlong localProcessStartDate = localProcess->getStartDate();
		logInfo("Local process start date = %lld", localProcessStartDate);

		logInfo("");
		logInfo("Getting local process real memory usage (bytes)...");
		jlong localProcessRMU = localProcess->getRealMemoryUsage();
		logInfo("Local process real memory usage = %lld", localProcessRMU);

		logInfo("");
		logInfo("Getting local process virtual memory usage (bytes)...");
		jlong localProcessVMU = localProcess->getVirtualMemoryUsage();
		logInfo("Local process virtual memory usage = %lld", localProcessVMU);

		logInfo("");
		logInfo("Getting local process cpu usage...");
		jdouble cpuUsage = localProcess->getCpuUsage();
		logInfo("Local process virtual memory usage percentage = %f", cpuUsage);

		if (localProcess) {
			delete localProcess;
		}

	} catch (NativeException& e) {
		logError("NativeException thrown Class = %s Method = %s Message = %s Error Code = %d", e.getClassName().getString().c_str(), e.getMethodName().getString().c_str(), e.getMessage().getString().c_str(), e.getErrorCode());
		FAIL_TEST(TEST_NAME)
	} catch (...) {
		logError("Exception thrown in Main Method !");
		FAIL_TEST(TEST_NAME)
	}

	PASS_TEST(TEST_NAME)
}
