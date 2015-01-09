#include "jcpp/native/unixos/UnixUtils.h"
#include "jcpp/native/unixos/nthread/UnixThread.h"
#include "jcpp/native/api/NativeException.h"
#include "jcpp/native/api/nthread/ScopedLock.h"
#include "jcpp/native/unixos/nthread/UnixThreadPointerStorage.h"
#include <errno.h>
#include <unistd.h>
#include <stdio.h>

/*
 * Implement lwp user threads for solaris
 *
 */

namespace jcpp {
	namespace native {
		namespace unixos {
			namespace nthread {

				NativeString UnixThread::className("jcpp::native::unixos::thread::UnixThread");
				UnixMutex UnixThread::uniqueIdMutex;
				jlong UnixThread::currenId = 0;

				UnixThread::UnixThread(NativeRunnable * runnable) :
						UnixAbstractThread(runnable),id(uniqueId()), joinMutex(), doneMutex(), runningMutex(), running(false), started(false), methodStartedMutex(), methodStarted(false) {
					name += "Thread id=";
					name += id;
				}

				UnixThread::~UnixThread() {
					if (isRunning()) {
#if defined(SOLARIS2)
						//TODO no equivalent for pthread_detach?
						pthread_detach(thread);
#else
						pthread_detach(thread); //TODO its usage?
#endif
					}
				}

				jlong UnixThread::uniqueId() {
					ScopedLock synchronize(uniqueIdMutex);
					return ++currenId;
				}

				void* UnixThread::runnableEntry(void* pThread) {
					UnixThread* unixThread = reinterpret_cast<UnixThread*>(pThread);

					unixThread->runningMutex.lock();
					unixThread->running = true;
					unixThread->runningMutex.unlock();

					unixThread->methodStartedMutex.lock();
					unixThread->methodStarted = true;
					unixThread->methodStartedMutex.unlock();

					ScopedLock doneSynchronize(unixThread->doneMutex);
					UnixThreadPointerStorage::getInstance()->set(unixThread);
					try {
						unixThread->state = NTH_RUNNABLE;
						unixThread->runnable->run();
					} catch (...) {
						// TODO check what todo
						//TODO Handler listener UncaughtExceptionHandler{}
					}
					unixThread->state = NTH_TERMINATED;
					unixThread->storage->clear();

					unixThread->runningMutex.lock();
					unixThread->running = false;
					unixThread->runningMutex.unlock();

					ScopedLock mutexSynchronize(unixThread->mutex);
					unixThread->runnable = null;

					if(unixThread->isDeleteOnFinish()) {
						delete unixThread;
					}

					return 0;
				}


				jlong UnixThread::getId() const {
					return id;
				}

				void UnixThread::start() {
					ScopedLock synchronize(mutex);
					if (isRunning()) {
						throw NativeException(className, "start", SYSTEM_EXCEPTION, "thread already running");
					}
					if (runnable == null) {
						throw NativeException(className, "start", ILLEGAL_STATE_EXCEPTION, "Threads can be started one time only!");
					}

#if defined(SOLARIS2)
					if (thr_create(NULL, 0, runnableEntry, this, 0, &thread)){
						runnable = NULL;
						throw NativeException(className, "start", SYSTEM_EXCEPTION, "Cannot start thread");
					}
#else
					pthread_attr_t attributes;
					pthread_attr_init(&attributes);

					if (pthread_create(&thread, &attributes, runnableEntry, this)) {
						runnable = null;
						pthread_attr_destroy(&attributes);
						throw NativeException(className, "start", SYSTEM_EXCEPTION, "Cannot start thread");
					}
					pthread_attr_destroy(&attributes);
#endif

					started = true;

					if ((priority != NORMAL)) {
						struct sched_param par;
						par.sched_priority = priorityToNativePriority();

#if defined(SOLARIS2)
						if (thr_setprio(thread, par.sched_priority)){
#else
						if (pthread_setschedparam(thread, SCHED_OTHER, &par)) {
#endif
							throw NativeException(className, "setPriority", SYSTEM_EXCEPTION, "cannot set thread priority");
						}
					}
				}

				void UnixThread::join() {
					if(started) {
					ScopedLock synchronize(joinMutex);

						jlong startWaitForMethodStarted =  UnixUtils::getCurrentTimeMillis();
						while(true) {
							if ((UnixUtils::getCurrentTimeMillis() - startWaitForMethodStarted) > 30000) {
								printf("THE LOOP TIMED OUT\n");
								break;
							}
							this->sleep(100);
							ScopedLock synchronizeMethodStarted(methodStartedMutex);
							if(methodStarted){
								break;
							}
						}

						if (isRunning()) {
#if defined(SOLARIS2)
							if (thr_join(thread, NULL, NULL)){
								throw NativeException(className, "join", SYSTEM_EXCEPTION, "cannot join thread");
							}
#else
							void* result;
							if (pthread_join(thread, &result)) {
								throw NativeException(className, "join", SYSTEM_EXCEPTION, "cannot join thread");
							}
#endif
						}
					}
				}

				jbool UnixThread::join(jlong milliseconds) {
					ScopedLock synchronize(joinMutex);
					if (!isRunning()) {
						return true;
					}
					jbool locked = doneMutex.tryLock(milliseconds);
					if (locked) {
						doneMutex.unlock();
						return true;
					}
					return false;
				}

				jbool UnixThread::isRunning() {
					jbool returnValue = false;
					runningMutex.lock();
					returnValue = running;
					runningMutex.unlock();
					return returnValue;
				}

				void UnixThread::sleep(jlong milliseconds) {
					UnixUtils::sleep(milliseconds);
				}

			}
		}
	}
}
