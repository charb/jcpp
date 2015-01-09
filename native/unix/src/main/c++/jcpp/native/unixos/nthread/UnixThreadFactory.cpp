#include "jcpp/native/unixos/nthread/UnixThreadFactory.h"
#include "jcpp/native/unixos/nthread/UnixMutex.h"
#include "jcpp/native/unixos/nthread/UnixCondition.h"
#include "jcpp/native/unixos/nthread/UnixThread.h"
#include "jcpp/native/unixos/nthread/UnixMainThread.h"
#include "jcpp/native/unixos/nthread/UnixThreadPointerStorage.h"
#include "jcpp/native/api/nthread/ScopedLock.h"

#if defined(Linux)
#include <signal.h>
#endif

namespace jcpp {
	namespace native {
		namespace unixos {
			namespace nthread {

#if defined(Linux)
				void resume_handler(int sig){
					//no action necessary, need to this signal handler it to override default behavior of terminating the process
				}

				void suspend_handler(int sig){
					sigset_t mask;
					sigfillset(&mask);
					sigdelset(&mask, SIG_RESUME); //sigsuspend blocks all signals in the mask, deleting SIG_RESUME from mask means sigsuspend will not block it.
					sigsuspend(&mask); //suspends untill SIG_RESUME is recieved (suspends until a signal outside the mask is recieved)
				}
#endif

				UnixThreadFactory::UnixThreadFactory() {
					mutex = createNativeMutex();
#if defined(Linux)
					signal(SIG_SUSPEND, suspend_handler); //install a signal handler for the given signal
					signal(SIG_RESUME, resume_handler);
#endif
				}

				UnixThreadFactory::~UnixThreadFactory() {

				}

				NativeMutex * UnixThreadFactory::createNativeMutex() {
					return new UnixMutex();
				}

				NativeCondition * UnixThreadFactory::createNativeCondition(NativeMutex * mutex) {
					return new UnixCondition((UnixMutex *) mutex);
				}

				NativeThread * UnixThreadFactory::createNativeThread(NativeRunnable * runnable) {
					ScopedLock lock(*mutex);
					UnixThread * thread = new UnixThread(runnable);
					threads.push_back(thread);
					return thread;
				}

				NativeThread * UnixThreadFactory::currentThread() {
					UnixThread* current = UnixThreadPointerStorage::getInstance()->get();
					return current == null ? mainThread() : current;
				}

				NativeThread * UnixThreadFactory::mainThread() {
					return UnixMainThread::getInstance();
				}

			}
		}
	}
}
