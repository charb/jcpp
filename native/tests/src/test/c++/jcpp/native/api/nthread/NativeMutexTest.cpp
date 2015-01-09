#include "NativeTestUtils.h"
#include "jcpp/native/api/NativeFactory.h"

#define TEST_NAME "Native Mutex"

using namespace jcpp::native::api;
using namespace jcpp::native::api::nthread;

int main(int argc, char *argv[]) {
	logTitle(TEST_NAME);

	NativeThreadFactory * threadFactory = NativeFactory::getNativeThreadFactory();

	NativeMutex * mutex = threadFactory->createNativeMutex();

	ASSERT_TRUE_M(mutex, "Tested create native mutex", "Null mutex was returned from the factory's createNativeMutex method", TEST_NAME);

	mutex->lock();

	ASSERT_TRUE_M(mutex->tryLock(), "Tested trylock mutex while it is locked", "Could not try to lock mutex while we already hold the lock", TEST_NAME);

	mutex->unlock();

	delete mutex;

	PASS_TEST(TEST_NAME)
}
