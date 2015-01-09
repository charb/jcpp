#include "NativeTestUtils.h"
#include "jcpp/native/api/NativeFactory.h"
#include "jcpp/native/api/nthread/NativeThreadLocal.h"
#include "jcpp/native/api/NativeException.h"

#define TEST_NAME "Native Thread"

using namespace jcpp::native::api;
using namespace jcpp::native::api::nthread;

#define CHECK(R,E,PM,EM,ID) if(R == E) { logInfo(PM); } else { logError(EM); testsPassed = false; logSection("Exiting Runnable id = %d [FAILED]", ID); return; }
#define CHECK_TRUE(R,PM,EM,ID) if(R) { logInfo(PM); } else { logError(EM); testsPassed = false; logSection("Exiting Runnable id = %d [FAILED]", ID); return; }

#define CHECK_EM(R,E,EM,ID) if(R == E) { } else { logError(EM), testsPassed = false; logSection("Exiting Runnable id = %d [FAILED]", ID); return; }
#define CHECK_TRUE_EM(R,EM,ID) if(R) { } else { logError(EM); testsPassed = false; logSection("Exiting Runnable id = %d [FAILED]", ID); return; }

//~-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//~ Thread Test Runnable
//~-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TestRunnable: public NativeRunnable {
public:

	jint id;
	jbool testsPassed;

	TestRunnable(jint id) :
			id(id), testsPassed(true) {
	}

	virtual void run() {
		logSection("Starting Test Runnable id = %d", id);

		NativeSystem * system = NativeFactory::getNativeSystem();
		NativeThreadFactory * threadFactory = NativeFactory::getNativeThreadFactory();

		NativeThread * currentThread = threadFactory->currentThread();

		CHECK_TRUE(currentThread, "Tested getting the new thread", "Failed to get the new thread", id);
		CHECK_TRUE(currentThread->isRunning(), "Tested isRunning on new thread", "IsRunning return false for the new thread", id);
		CHECK_TRUE(currentThread->getId() > 0, "Tested getting the id of the new thread", "Current Thread id is not positive", id);

		jlong start = system->currentTimeMillis();
		currentThread->sleep(200);
		jlong end = system->currentTimeMillis();
		logInfo("Slept for: %lld ms", (end - start));

		currentThread->yield();
		logInfo("Tested yield on new thread");

		currentThread->setPriority(HIGH);
		CHECK(currentThread->getPriority(), HIGH, "Tested setting priority to HIGH on the new thread", "Failed to set priority to HIGH on the new thread", id);

		currentThread->setPriority(NORMAL);
		CHECK(currentThread->getPriority(), NORMAL, "Tested setting priority back to NORMAL on the new thread", "Failed to set priority back to NORMAL on the new thread", id);

		NativeThreadLocalStorage * newThreadStorage = currentThread->getStorage();
		CHECK_TRUE(newThreadStorage, "Tested getting the new thread local storage", "Failed to get the new thread local storage", id);

		NativeThreadLocalStorage * currentThreadStorage = NativeThreadLocalStorage::current();
		CHECK_TRUE(currentThreadStorage, "Tested getting the current thread local storage", "Failed to get the current thread local storage", id);

		CHECK(currentThreadStorage, newThreadStorage, "Tested equating the current thread local storage to the new thread local storage", "Current thread local storage not equal to the new thread local storage", id);

		logSection("Exiting Runnable id = %d [PASSED]", id);
	}

};

//~-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//~ Thread Local Runnable
//~-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class ThreadLocalRunnable: public NativeRunnable {
public:

	jint id;
	jbool testsPassed;

	static NativeThreadLocal threadlocal;

	ThreadLocalRunnable(int id) :
			NativeRunnable(), id(id), testsPassed(true) {
	}

	virtual ~ThreadLocalRunnable() {
	}

	virtual void run() {
		logSection("Starting Thread Local Runnable id = %d", id);

		jint* array[1000];
		for (jint i = 0; i < 1000; i++) {
			array[i] = new jint;
			*array[i] = id + i;
		}

		for (jint i = 0; i < 1000; i++) {
			*threadlocal = array[i];
			CHECK_EM((*((jint * )(*threadlocal))), id + i, "Failed to get correct thread local value.", id);
		}

		NativeThreadFactory * threadFactory = NativeFactory::getNativeThreadFactory();
		NativeThread * currentThread = threadFactory->currentThread();
		for (jint i = 0; i < 1000; i++) {
			*threadlocal = array[i];
			currentThread->sleep(1);
			CHECK_EM((*((jint * )(*threadlocal))), id + i, "Failed to get correct thread local value.", id);
		}

		logSection("Exiting Runnable id = %d [PASSED]", id);
	}

};

//~-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//~ Mutex Runnables
//~-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

NativeThreadLocal ThreadLocalRunnable::threadlocal;

class MasterMutexRunnable: public NativeRunnable {
public:

	jint id;
	jbool testsPassed;
	NativeMutex * mutex;

	MasterMutexRunnable(int id, NativeMutex * mutex) :
			NativeRunnable(), id(id), testsPassed(true), mutex(mutex) {
	}

	virtual ~MasterMutexRunnable() {
	}

	virtual void run() {
		logSection("Starting Master Mutex Runnable id = %d", id);

		NativeSystem * system = NativeFactory::getNativeSystem();
		NativeThreadFactory * threadFactory = NativeFactory::getNativeThreadFactory();
		NativeThread * currentThread = threadFactory->currentThread();

		jlong start = system->currentTimeMillis();
		logInfo("Acquiring lock 1 in MASTER runnable...");
		mutex->lock();
		logInfo("Acquired lock 1 in MASTER runnable...");
		jlong end = system->currentTimeMillis();

		if ((end - start) > 10) {
			logError("Lock 1 was establish slowly in MASTER mutex runnable");
			testsPassed = false;
			logSection("Exiting Runnable id = %d [FAILED]", id);
			mutex->unlock();
			return;
		}

		logInfo("Sleeping for 200 ms in MASTER runnable...");
		currentThread->sleep(200);
		logInfo("Woke up after 200 ms in MASTER runnable...");

		logInfo("Unlocking lock 1 in MASTER runnable...");
		mutex->unlock();
		logInfo("Unlocked lock 1 in MASTER runnable...");

		logInfo("Sleeping for 1 ms in MASTER runnable...");
		currentThread->sleep(1);
		logInfo("Woke up after 1 ms in MASTER runnable...");

		start = system->currentTimeMillis();
		logInfo("Acquiring lock 2 in MASTER runnable...");
		mutex->lock();
		logInfo("Acquired lock 2 in MASTER runnable...");
		end = system->currentTimeMillis();

		logInfo("Unlocking lock 2 in MASTER runnable...");
		mutex->unlock();
		logInfo("Unlocked lock 2 in MASTER runnable...");

		if ((end - start) < 100) {
			logError("Lock 2 was establish quickly in MASTER mutex runnable");
			testsPassed = false;
			logSection("Exiting Runnable id = %d [FAILED]", id);
			return;
		}

		logSection("Exiting Runnable id = %d [PASSED]", id);
	}

};

class SlaveMutexRunnable: public NativeRunnable {
public:

	jint id;
	jbool testsPassed;
	NativeMutex * mutex;

	SlaveMutexRunnable(int id, NativeMutex * mutex) :
			NativeRunnable(), id(id), testsPassed(true), mutex(mutex) {
	}

	virtual ~SlaveMutexRunnable() {
	}

	virtual void run() {
		logSection("Starting Slave Mutex Runnable id = %d", id);

		NativeSystem * system = NativeFactory::getNativeSystem();
		NativeThreadFactory * threadFactory = NativeFactory::getNativeThreadFactory();
		NativeThread * currentThread = threadFactory->currentThread();

		currentThread->sleep(10);

		jlong start = system->currentTimeMillis();
		logInfo("Acquiring lock in SLAVE runnable...");
		mutex->lock();
		logInfo("Acquired lock in SLAVE runnable...");
		jlong end = system->currentTimeMillis();

		if ((end - start) < 100) {
			logError("Lock 1 was establish quickly in SLAVE mutex runnable");
			testsPassed = false;
			logSection("Exiting Runnable id = %d [FAILED]", id);
			mutex->unlock();
			return;
		}

		logInfo("Sleeping for 200 ms in SLAVE runnable...");
		currentThread->sleep(200);
		logInfo("Woke up after 200 ms in SLAVE runnable...");

		logInfo("Unlocking lock in SLAVE runnable...");
		mutex->unlock();
		logInfo("Unlocked lock in SLAVE runnable...");

		logSection("Exiting Runnable id = %d [PASSED]", id);
	}

};

//~-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//~ Suspand Runnable
//~-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class SuspendMutexRunnable: public NativeRunnable {
public:

	jint id;
	jbool testsPassed;
	NativeMutex * mutex;

	SuspendMutexRunnable(int id, NativeMutex * mutex) :
			NativeRunnable(), id(id), testsPassed(true), mutex(mutex) {
	}

	virtual ~SuspendMutexRunnable() {
	}

	virtual void run() {
		logSection("Starting Suspend Mutex Runnable id = %d", id);

		NativeSystem * system = NativeFactory::getNativeSystem();
		NativeThreadFactory * threadFactory = NativeFactory::getNativeThreadFactory();
		NativeThread * currentThread = threadFactory->currentThread();

		jlong start = system->currentTimeMillis();
		logInfo("Acquiring lock in Suspend Mutex Runnable...");
		mutex->lock();
		logInfo("Acquired lock in Suspend Mutex Runnable...");
		jlong end = system->currentTimeMillis();
		mutex->unlock();

		if ((end - start) < 500) {
			logError("Lock was establish quickly in Suspend mutex runnable");
			testsPassed = false;
			logSection("Exiting Runnable id = %d [FAILED]", id);
			return;
		}

		logSection("Exiting Runnable id = %d [PASSED]", id);
	}

};

//~-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//~ Condition Runnables
//~-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class ConditionMasterRunnable: public NativeRunnable {
public:

	jint id;
	jbool testsPassed;
	NativeCondition * condition;

	ConditionMasterRunnable(int id, NativeCondition * condition) :
			NativeRunnable(), id(id), testsPassed(true), condition(condition) {
	}

	virtual ~ConditionMasterRunnable() {
	}

	virtual void run() {
		logSection("Starting Master Condition Runnable id = %d", id);

		try {

			NativeThreadFactory * threadFactory = NativeFactory::getNativeThreadFactory();
			NativeThread * currentThread = threadFactory->currentThread();

			logInfo("Sleeping for 500 ms in Master Condition Thread");
			currentThread->sleep(500);

			logInfo("Acquiring condition lock in Master Condition Runnable...");
			condition->getMutex()->lock();
			logInfo("Acquired condition lock in Master Condition Runnable...");

			logInfo("Notifying all waiting threads in Master Condition Runnable...");
			jbool notified = condition->notifyAll();
			if (notified) {
				logInfo("Master Condition Runnable has notified waiting threads successfully");
			} else {
				testsPassed = false;
				logError("Master Condition Runnable has failed to notify waiting threads!");
			}

			logInfo("Unlocking condition lock in Master Condition Runnable...");
			condition->getMutex()->unlock();
			logInfo("Unlocked condition lock in Master Condition Runnable...");

		} catch (NativeException& e) {
			testsPassed = false;
			logError("NativeException thrown in Master Condition Runnable id = %d Class = %s Method = %s Message = %s", id, e.getClassName().getString().c_str(), e.getMethodName().getString().c_str(), e.getMessage().getString().c_str());
			logSection("Exiting Runnable id = %d [FAILED]", id);
			return;
		} catch (...) {
			logError("Exception thrown in Master Condition Runnable id = %d", id);
			logSection("Exiting Runnable id = %d [FAILED]", id);
		}
		if (testsPassed) {
			logSection("Exiting Runnable id = %d [PASSED]", id);
		} else {
			logSection("Exiting Runnable id = %d [FAILED]", id);
		}
	}

};

class ConditionSlaveRunnable: public NativeRunnable {
public:

	jint id;
	jbool testsPassed;
	NativeCondition * condition;

	ConditionSlaveRunnable(int id, NativeCondition * condition) :
			NativeRunnable(), id(id), testsPassed(true), condition(condition) {
	}

	virtual ~ConditionSlaveRunnable() {
	}

	virtual void run() {
		logSection("Starting Slave Condition Runnable id = %d", id);

		try {

			NativeSystem * system = NativeFactory::getNativeSystem();
			NativeThreadFactory * threadFactory = NativeFactory::getNativeThreadFactory();
			NativeThread * currentThread = threadFactory->currentThread();

			jlong start = system->currentTimeMillis();

			logInfo("Acquiring condition lock in Slave Condition Runnable id = %d", id);
			condition->getMutex()->lock();
			logInfo("Acquired condition lock in Slave Condition Runnable id = %d", id);

			logInfo("Waiting on condition in Slave Condition Runnable id = %d", id);
			jbool notified = condition->wait();
			if (notified) {
				logInfo("Slave Condition Runnable id = %d was notified successfully", id);
			} else {
				testsPassed = false;
				logError("Slave Condition Runnable id = %d was not notified while waiting!", id);
			}

			logInfo("Unlocking condition lock in Slave Condition Runnable id = %d", id);
			condition->getMutex()->unlock();
			logInfo("Unlocked condition lock in Slave Condition Runnable id = %d", id);

			jlong end = system->currentTimeMillis();

			if ((end - start) > 1500) {
				testsPassed = false;
				logError("Slave Condition Runnable took time more than expected %lld milli seconds!", (end - start));
			}

		} catch (NativeException& e) {
			testsPassed = false;
			logError("NativeException thrown in Slave Condition Runnable id = %d Class = %s Method = %s Message = %s", id, e.getClassName().getString().c_str(), e.getMethodName().getString().c_str(), e.getMessage().getString().c_str());
			logSection("Exiting Runnable id = %d [FAILED]", id);
			return;
		} catch (...) {
			testsPassed = false;
			logError("Exception thrown in Slave Condition Runnable id = %d", id);
			logSection("Exiting Runnable id = %d [FAILED]", id);
			return;
		}

		if (testsPassed) {
			logSection("Exiting Runnable id = %d [PASSED]", id);
		} else {
			logSection("Exiting Runnable id = %d [FAILED]", id);
		}
	}

};

//~-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//~ Main Method
//~-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main(int argc, char *argv[]) {
	logTitle(TEST_NAME);

	NativeSystem * system = NativeFactory::getNativeSystem();
	NativeThreadFactory * threadFactory = NativeFactory::getNativeThreadFactory();

	//~ -------------------------------------------
	//~ Main Thread Test
	//~ -------------------------------------------

	NativeThread * mainThread = threadFactory->mainThread();

	ASSERT_TRUE_M(mainThread, "Tested getting the main thread", "Failed to get the main thread", TEST_NAME);
	ASSERT_TRUE_M(mainThread->isRunning(), "Tested isRunning on main thread", "IsRunning return false for the main thread", TEST_NAME);

	ASSERT_M(mainThread->getId(), 0, "Tested getting the id of the main thread (0)", "Main Thread id is not 0", TEST_NAME);

	logInfo("Getting current Time in Millis");
	jlong start = system->currentTimeMillis();
	logInfo("Current Time in Millis = %lld", start);
	logInfo("Sleeping for 100ms in main thread");
	mainThread->sleep(100);
	logInfo("Getting current Time in Milli Second");
	jlong end = system->currentTimeMillis();
	logInfo("Slept for: %lld ms", (end - start));

	mainThread->yield();
	logInfo("Tested yield on main thread");

#if defined(_AIX)
	try{
	mainThread->setPriority(HIGH);
	}catch(NativeException &e){
		logInfo("Changing thread priority to HIGH failed\n");
	}
#else
	mainThread->setPriority(HIGH);
#endif

	ASSERT_M(mainThread->getPriority(), HIGH, "Tested setting priority to HIGH on the main thread", "Failed to set priority to HIGH on the main thread", TEST_NAME);

#if defined(_AIX)
	try{
	mainThread->setPriority(NORMAL);
	}catch(NativeException &e){
		logInfo("Changing thread priority to NORMAL failed\n");
	}
#else
	mainThread->setPriority(NORMAL);
#endif

	ASSERT_M(mainThread->getPriority(), NORMAL, "Tested setting priority back to NORMAL on the main thread", "Failed to set priority back to NORMAL on the main thread", TEST_NAME);

	NativeThreadLocalStorage * mainThreadStorage = mainThread->getStorage();
	ASSERT_TRUE_M(mainThreadStorage, "Tested getting the main thread local storage", "Failed to get the main thread local storage", TEST_NAME);

	NativeThreadLocalStorage * currentThreadStorage = NativeThreadLocalStorage::current();
	ASSERT_TRUE_M(currentThreadStorage, "Tested getting the current thread local storage", "Failed to get the current thread local storage", TEST_NAME);

	ASSERT_M(currentThreadStorage, mainThreadStorage, "Tested equating the current thread local storage to the main thread local storage", "Current thread local storage not equal to the main thread local storage", TEST_NAME);

	//~ -------------------------------------------
	//~ Test Runnable Test
	//~ -------------------------------------------

	TestRunnable * runnable1 = new TestRunnable(1);
	NativeThread * thread1 = threadFactory->createNativeThread(runnable1);
	ASSERT_TRUE_M(thread1, "Tested creating a new thread from the thread factory", "Failed to create a new thread from the thread factory", TEST_NAME);
	ASSERT_TRUE_M(!thread1->isRunning(), "Tested isRunning on the new thread before starting", "IsRunning return true for the new thread before it was started", TEST_NAME);

	thread1->start();

	logInfo("Sleeping for 100ms in main thread");
	mainThread->sleep(100);

	ASSERT_TRUE_M(thread1->isRunning(), "Tested isRunning on the new thread after starting", "IsRunning return false for the new thread after it was started", TEST_NAME);

	thread1->join();
	logInfo("Tested join on new thread");

	if (!runnable1->testsPassed) {
		delete runnable1;
		FAIL_TEST(TEST_NAME);
	}
	delete runnable1;

	//~ -------------------------------------------
	//~ Thread Local Runnable Test
	//~ -------------------------------------------

	ThreadLocalRunnable * runnable2 = new ThreadLocalRunnable(2);
	NativeThread * thread2 = threadFactory->createNativeThread(runnable2);

	ThreadLocalRunnable * runnable3 = new ThreadLocalRunnable(3000);
	NativeThread * thread3 = threadFactory->createNativeThread(runnable3);

	thread2->start();
	thread3->start();

	thread2->join();
	thread3->join();

	if (!runnable2->testsPassed) {
		delete runnable2;
		delete runnable3;
		FAIL_TEST(TEST_NAME);
	}
	delete runnable2;

	if (!runnable3->testsPassed) {
		delete runnable3;
		FAIL_TEST(TEST_NAME);
	}
	delete runnable3;

	//~ -------------------------------------------
	//~ Mutex Runnable Test
	//~ -------------------------------------------

	NativeMutex * mutex = threadFactory->createNativeMutex();

	MasterMutexRunnable * runnable4 = new MasterMutexRunnable(4, mutex);
	NativeThread * thread4 = threadFactory->createNativeThread(runnable4);

	SlaveMutexRunnable * runnable5 = new SlaveMutexRunnable(5, mutex);
	NativeThread * thread5 = threadFactory->createNativeThread(runnable5);

	thread4->start();
	thread5->start();

	thread4->join();
	thread5->join();

	delete mutex;

	if (!runnable4->testsPassed) {
		delete runnable4;
		delete runnable5;
		FAIL_TEST(TEST_NAME);
	}
	delete runnable4;

	if (!runnable5->testsPassed) {
		delete runnable5;
		FAIL_TEST(TEST_NAME);
	}
	delete runnable5;

	//~ -------------------------------------------
	//~ Suspend Runnable Test !!!! Still not implemented on UNIX
	//~ -------------------------------------------

	NativeMutex * mutex2 = threadFactory->createNativeMutex();

	SuspendMutexRunnable * runnable6 = new SuspendMutexRunnable(6, mutex2);
	NativeThread * thread6 = threadFactory->createNativeThread(runnable6);

	logInfo("Locking Suspend Mutex in main thread");
	mutex2->lock();
	logInfo("Locked Suspend Mutex in main thread");
	logInfo("Starting Suspend Runnable Thread");
	thread6->start();
	logInfo("Sleeping for 100ms in main thread");
	mainThread->sleep(100);
	logInfo("Suspending Suspend Runnable Thread");
	thread6->suspend();
	logInfo("UnLocking Suspend Mutex in main thread");
	mutex2->unlock();
	logInfo("UnLocked Suspend Mutex in main thread");
	logInfo("Sleeping for 500ms in main thread");
	mainThread->sleep(500);
	logInfo("Resuming Suspend Runnable Thread");
	thread6->resume();
	logInfo("Joining Suspend Runnable Thread ");
	thread6->join();

	delete runnable6;
	delete mutex2;

	if (!runnable6->testsPassed) {
		FAIL_TEST(TEST_NAME);
	}


	//~ -------------------------------------------
	//~ Condition Runnable Test // Sleeping while using monitors on unix is causing issues
	//~ -------------------------------------------

	NativeMutex * conditionMutex = threadFactory->createNativeMutex();
	NativeCondition * condition = threadFactory->createNativeCondition(conditionMutex);

	logInfo("Creating Condition Master Thread...");
	ConditionMasterRunnable * runnable7 = new ConditionMasterRunnable(7, condition);
	NativeThread * thread7 = threadFactory->createNativeThread(runnable7);

	std::vector<ConditionSlaveRunnable *> monitorSlaveRunnables;
	std::vector<NativeThread *> monitorSlaveThreads;
	int i = 0;

	logInfo("Creating Condition Slave Threads...");
	for (i = 0; i < 10; i++) {
		ConditionSlaveRunnable * conditionSlaveRunnable = new ConditionSlaveRunnable(8 + i, condition);
		monitorSlaveRunnables.push_back(conditionSlaveRunnable);
		NativeThread * monitorSlavethread = threadFactory->createNativeThread(conditionSlaveRunnable);
		monitorSlaveThreads.push_back(monitorSlavethread);
	}

	logInfo("Starting Condition Slave Threads...");
	for (std::vector<NativeThread *>::iterator it = monitorSlaveThreads.begin(); it != monitorSlaveThreads.end(); ++it) {
		(*it)->start();
	}
	logInfo("Sleeping for 500ms in main thread");
	mainThread->sleep(500);
	logInfo("Starting Condition Master Thread...");
	thread7->start();

	logInfo("Joining Condition Master Thread...");
	thread7->join();
	logInfo("Joining Condition Slave Threads...");
	for (std::vector<NativeThread *>::iterator it = monitorSlaveThreads.begin(); it != monitorSlaveThreads.end(); ++it) {
		(*it)->join();
	}

	delete thread7;
	thread7 = null;
	for (std::vector<NativeThread *>::iterator it = monitorSlaveThreads.begin(); it != monitorSlaveThreads.end(); ++it) {
		delete *it;
	}
	monitorSlaveThreads.clear();

	jbool monitorRunnableFailed = false;
	if (!runnable7->testsPassed) {
		monitorRunnableFailed = true;
	}
	delete runnable7;
	runnable7 = null;
	for (std::vector<ConditionSlaveRunnable *>::iterator it = monitorSlaveRunnables.begin(); it != monitorSlaveRunnables.end(); ++it) {
		if (!(*it)->testsPassed) {
			monitorRunnableFailed = true;
		}
		delete *it;
	}
	monitorSlaveRunnables.clear();

	delete condition;
	delete conditionMutex;

	if (monitorRunnableFailed) {
		FAIL_TEST(TEST_NAME);
	}

	PASS_TEST(TEST_NAME)
}

