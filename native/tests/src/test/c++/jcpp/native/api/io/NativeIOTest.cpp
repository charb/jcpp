#include "NativeTestUtils.h"
#include "jcpp/native/api/NativeFactory.h"

#include <iostream>

#define TEST_NAME "Native IO"

using namespace jcpp::native::api;
using namespace jcpp::native::api::io;

// TODO test write with large data size (make sure no limit on buffer size like sockets)
int main(int argc, char *argv[]) {
	logTitle(TEST_NAME);

	NativeIOFactory * factory = NativeFactory::getNativeIOFactory();
	NativeFileFactory * fileFactory = NativeFactory::getNativeFileFactory();
	NativeThreadFactory * threadFactory = NativeFactory::getNativeThreadFactory();

	try {

//		logInfo("Testing read from Standard Input Stream, please input \"test\" and hit enter");
//		NativeInputStream * stdInStream = factory->getStandardInputStream();
//		jbyte inBuf[4];
//		jint nStdIN = stdInStream->read(inBuf, 0, 4);
//		ASSERT_M(nStdIN, 4, "Read successfully 4 bytes from the Standard Input Stream", "Failed to read 4 bytes from the Standard Input Stream", TEST_NAME)
//		ASSERT_EM(inBuf[0], 't', "Failed to read correct letters from the File Input Stream", TEST_NAME)
//		ASSERT_EM(inBuf[1], 'e', "Failed to read correct letters from the File Input Stream", TEST_NAME)
//		ASSERT_EM(inBuf[2], 's', "Failed to read correct letters from the File Input Stream", TEST_NAME)
//		ASSERT_M(inBuf[3], 't', "Read successfully \"test\" from the Standard Input Stream", "Failed to read correct letters from the File Input Stream", TEST_NAME)

		logInfo("Testing write and flush on Standard Output Stream");
		NativeString outStr = "Output Stream Test Text";
		NativeOutputStream * stdOutStream = factory->getStandardOutputStream();
		stdOutStream->write((jbyte *) outStr.getString().c_str(), 0, outStr.length());
		stdOutStream->flush();

		logInfo("Testing write and flush on Standard Error Stream");
		NativeString errStr = "Error Stream Test Text";
		NativeOutputStream * stdErrStream = factory->getStandardErrorStream();
		stdErrStream->write((jbyte *) errStr.getString().c_str(), 0, errStr.length());
		stdErrStream->flush();

		NativeFile * testDirFile = fileFactory->createNativeFile("TestDir");
		testDirFile->createDirectories();

		NativeString testFilePath("TestDir/TestFile.txt");

		NativeFileOutputStream * outputStream = factory->createFileOutputStream(testFilePath, false);
		ASSERT_TRUE_M(outputStream, "Tested creating a File Output Stream.", "Failed to create a File Output Stream", TEST_NAME)
		ASSERT_TRUE_M(outputStream->getNativeFileDescriptor(), "Tested getting the Native File Descriptor.", "Failed to get the Native File Descriptor", TEST_NAME)

		logInfo("Testing write, flush and close on File Output Stream");
		NativeString textStr = "File Test Text";
		outputStream->write((jbyte *) textStr.getString().c_str(), 0, 4);
		outputStream->write((jbyte *) textStr.getString().c_str(), 4, textStr.length() - 4);
		outputStream->flush();
		outputStream->close();
		delete outputStream;
		outputStream = null;

		NativeFileInputStream * inputStream = factory->createFileInputStream(testFilePath);
		ASSERT_TRUE_M(inputStream, "Tested creating a File Input Stream.", "Failed to create a File Input Stream", TEST_NAME)
		ASSERT_TRUE_M(inputStream->getNativeFileDescriptor(), "Tested getting the Native File Descriptor.", "Failed to get the Native File Descriptor", TEST_NAME)

		jbyte buf[4];
		jint n = inputStream->read(buf, 0, 4);
		ASSERT_M(n, 4, "Read successfully 4 bytes from the File Input Stream", "Failed to read 4 bytes from the File Input Stream", TEST_NAME)
		ASSERT_EM(buf[0], 'F', "Failed to read correct letters from the File Input Stream", TEST_NAME)
		ASSERT_EM(buf[1], 'i', "Failed to read correct letters from the File Input Stream", TEST_NAME)
		ASSERT_EM(buf[2], 'l', "Failed to read correct letters from the File Input Stream", TEST_NAME)
		ASSERT_M(buf[3], 'e', "Tested reading from the File Input Stream", "Failed to read correct letters from the File Input Stream", TEST_NAME)

		jlong availableBytes = inputStream->available();
		ASSERT_M(availableBytes, 10, "Tested getting available bytes from the File Input Stream", "Failed to get correct number of available bytes from the File Input Stream", TEST_NAME)

		jlong skipped = inputStream->skip(6);
		ASSERT_M(skipped, 6, "Tested skipping 6 bytes from the File Input Stream", "Failed to skip 6 bytes from the File Input Stream", TEST_NAME)

		inputStream->read(buf, 0, 1);
		inputStream->read(buf, 1, 2);
		inputStream->read(buf, 3, 1);
		ASSERT_EM(buf[0], 'T', "Failed to read correct letters from the File Input Stream after skipping 6 bytes", TEST_NAME)
		ASSERT_EM(buf[1], 'e', "Failed to read correct letters from the File Input Stream after skipping 6 bytes", TEST_NAME)
		ASSERT_EM(buf[2], 'x', "Failed to read correct letters from the File Input Stream after skipping 6 bytes", TEST_NAME)
		ASSERT_M(buf[3], 't', "Tested reading from the File Input Stream after skipping 6 bytes", "Failed to read correct letters from the File Input Stream after skipping 6 bytes", TEST_NAME)

		inputStream->close();
		delete inputStream;
		inputStream = null;

		testDirFile->remove(true);
		delete testDirFile;
	} catch (...) {
		logError("Exception Thrown ... ");
		FAIL_TEST(TEST_NAME)
	}

	PASS_TEST(TEST_NAME)
}
