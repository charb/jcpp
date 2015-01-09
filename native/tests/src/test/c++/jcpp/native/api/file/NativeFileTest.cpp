#include "NativeTestUtils.h"
#include "jcpp/native/api/NativeFactory.h"

#include <iostream>

#define TEST_NAME "Native File"

using namespace jcpp::native::api;
using namespace jcpp::native::api::file;

int main(int argc, char *argv[]) {
	logTitle(TEST_NAME);

	NativeFileFactory * factory = NativeFactory::getNativeFileFactory();

	NativeFile * file = factory->createNativeFile();
	ASSERT_NE_M(file, null, "Tested create default native file", "Null File returned from the factory's createNativeFile() method", TEST_NAME);

	logInfo("Default native file path = %s", file->getPath().getString().c_str());

	ASSERT_TRUE_M(file->exists(), "Tested file exists", "File exists returned false while the file actually exists", TEST_NAME);

	ASSERT_TRUE_M(!file->isAbsolute(), "Tested is Absolute on default file", "Default file return true for isAbsolute", TEST_NAME);

	file->normalise();

	logInfo("Normalised path = %s", file->getPath().getString().c_str());

	ASSERT_TRUE_M(file->isAbsolute(), "Tested is Absolute on the normalized default file", "After normalizing the file return false for isAbsolute", TEST_NAME);
	ASSERT_TRUE_M(file->exists(), "Tested exists on the normalized default file", "After normalizing file return false for exists", TEST_NAME);

	jlong freeSpace = file->getFreeSpace();
	ASSERT_TRUE_M(freeSpace > 0, "Tested free space", "Free Space returned a non positive number.", TEST_NAME);
	logInfo("Free space = %lld", freeSpace);

	jlong totalSpace = file->getTotalSpace();
	ASSERT_TRUE_M(totalSpace > 0, "Tested total space", "Total Space returned a non positive number.", TEST_NAME);
	logInfo("Total space = %lld", totalSpace);

	jlong usableSpace = file->getUsableSpace();
	ASSERT_TRUE_M(usableSpace > 0, "Tested usable space", "Usable Space returned a non positive number.", TEST_NAME);
	logInfo("Usable space = %lld", usableSpace);

	NativeFile * testFolder = factory->createNativeFile("TestFolder");
	ASSERT_TRUE_M(!testFolder->exists(), "Tested not exist on a folder that does not exist", "Test Folder returned true for exists while it was still not created", TEST_NAME);
	testFolder->createDirectory();
	logInfo("Test Folder path = %s", testFolder->getPath().getString().c_str());
	logInfo("Test Folder absolute path = %s", testFolder->getAbsolutePath().getString().c_str());
	ASSERT_TRUE_M(testFolder->exists(), "Tested exist on a folder created by the test", "Test Folder returned false for exists after it was created using createDirectory", TEST_NAME);
	ASSERT_TRUE_M(testFolder->isDirectory(), "Test isDirectory on the created folder", "Test Folder returned false for isDirectory", TEST_NAME);
	ASSERT_TRUE_M(!testFolder->isFile(), "Tested is not file on the created folder", "Test Folder returned true for isFile", TEST_NAME);
	ASSERT_TRUE_M(!testFolder->isHidden(), "Test in not hidden on the created folder", "Test Folder returned true for isHidden", TEST_NAME);

	jlong created = file->getCreatedTime();
	ASSERT_TRUE_M(created > 0, "Tested created time on the default file", "Created time returned a non positive number.", TEST_NAME);
	logInfo("Created = %lld", created);

	jlong lastModified = file->getLastModified();
	ASSERT_TRUE_M(lastModified > 0, "Tested last modified on the defule file", "Last Modified time returned a non positive number.", TEST_NAME);
	logInfo("lastModified = %lld", lastModified);

	NativeFile * testFile = factory->createNativeFile("TestFolder/testFile.txt");
	testFile->createFile();
	logInfo("Test File path = %s", testFile->getPath().getString().c_str());
	logInfo("Test File absolute path = %s", testFile->getAbsolutePath().getString().c_str());

	ASSERT_TRUE_M(testFile->exists(), "Tested exists on a newly created file", "Test File returned false for exists after it was created using createFile", TEST_NAME);
	ASSERT_TRUE_M(testFile->isFile(), "Tested is file on a newly created file", "Test File returned false for isFile", TEST_NAME);
	ASSERT_TRUE_M(!testFile->isDirectory(), "Tested is not directory on a newly created file", "Test File returned true for isDirectory", TEST_NAME);

	ASSERT_TRUE_M(testFile->canRead(), "Tested can read on a newly created file", "Test File returned false for canRead", TEST_NAME);
	ASSERT_TRUE_M(testFile->canWrite(), "Tested can write on a newly created file", "Test File returned false for canWrite", TEST_NAME);
	ASSERT_TRUE_M(!testFile->canExecute(), "Tested can not execute on a newly created file", "Test File returned true for canExecute", TEST_NAME);

	std::vector<NativeString> files;
	testFolder->list(files);
	ASSERT_M(files.size(), 1, "Tested the size of the directory listing of the create Test Folder", "Test Folder list return a size != 1", TEST_NAME);
	NativeString child = files[0];
	logInfo("Test Folder Child = %s", child.getString().c_str());

	testFile->renameTo("TestFolder/testFile2.txt");
	ASSERT_M(testFile->getPath(), "TestFolder/testFile2.txt", "Tested the path of the renamed test file", "renameTo did not change the file path", TEST_NAME);
	ASSERT_TRUE_M(testFile->exists(), "Tested exists on the renamed test file", "TestFolder/testFile.txt returned false for exists after it was renamed to TestFolder/testFile2.txt", TEST_NAME);

	testFile->moveTo("TestFolder/testFile.txt");
	ASSERT_M(testFile->getPath(), "TestFolder/testFile.txt", "Tested the path of the moved test file", "moveTo did not change the file path", TEST_NAME);
	ASSERT_TRUE_M(testFile->exists(), "Tested exists on the moved test file", "TestFolder/testFile2.txt returned false for exists after it was renamed to TestFolder/testFile.txt", TEST_NAME);

	testFile->copyTo("TestFolder/testFile2.txt");
	NativeFile * copiedFile = factory->createNativeFile("TestFolder/testFile2.txt");
	ASSERT_TRUE_M(copiedFile->exists(), "Tested exists on the copied test file", "TestFolder/testFile2.txt returned false for exists after it was copied from TestFolder/testFile.txt", TEST_NAME);

	testFolder->remove(true);
	ASSERT_TRUE_M(!testFolder->exists(), "Tested not exist on the deleted test folder", "Test Folder returned true for exists after it was removed", TEST_NAME);
	ASSERT_TRUE_M(!testFile->exists(), "Tested not exist on the deleted test file", "Test File returned true for exists after TestFolder was removed", TEST_NAME);
	ASSERT_TRUE_M(!copiedFile->exists(), "Tested not exist on the deleted copied test file", "Copied Test File returned true for exists after TestFolder was removed", TEST_NAME);

	delete file;
	delete testFolder;
	delete testFile;
	delete copiedFile;

	PASS_TEST(TEST_NAME)
}
