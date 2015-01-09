#include "NativeTestUtils.h"

void logTitle(const char *message, ...) {
	char * buf = new char[512];
	va_list args;
	va_start(args, message);
	vsprintf(buf, message, args);
	va_end(args);
	printf("\n####################################\n");
	printf("- Starting Test %s:\n", buf);
	printf("####################################\n\n");
	delete buf;
}

void logInfo(const char * message, ...) {
	char * buf = new char[512];
	va_list args;
	va_start(args, message);
	vsprintf(buf, message, args);
	va_end(args);
	printf(">>> %s\n", buf);
	delete buf;
}

void logError(const char * message, ...) {
	char * buf = new char[512];
	va_list args;
	va_start(args, message);
	vsprintf(buf, message, args);
	va_end(args);
	printf("!!!ERROR: %s !!!\n", buf);
	delete buf;
}

void logSection(const char * message, ...) {
	char * buf = new char[512];
	va_list args;
	va_start(args, message);
	vsprintf(buf, message, args);
	va_end(args);
	printf("\n------------------------------------\n");
	printf("- %s\n", buf);
	printf("------------------------------------\n\n");
	delete buf;
}


void logEnd(const char * message, bool passed) {
	printf("\n************************************\n");
	printf("- Test %s ended [%s]\n", message, (passed ? "PASSED" : "FAILED"));
	printf("************************************\n\n");
}
