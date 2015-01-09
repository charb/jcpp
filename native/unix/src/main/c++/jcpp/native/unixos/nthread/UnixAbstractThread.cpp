#include "jcpp/native/unixos/UnixUtils.h"
#include "jcpp/native/unixos/nthread/UnixAbstractThread.h"
#include "jcpp/native/api/NativeException.h"
#include "jcpp/native/api/nthread/ScopedLock.h"
#include <errno.h>

#if defined(Linux)
#include <execinfo.h>
#include <signal.h>
#endif

#if defined(SOLARIS2)
#include <ucontext.h>
#include <dlfcn.h>
#endif

using namespace jcpp::native::api::nthread;

namespace jcpp {
	namespace native {
		namespace unixos {
			namespace nthread {

				NativeString UnixAbstractThread::className("jcpp::native::unixos::thread::UnixAbstractThread");

				UnixAbstractThread::UnixAbstractThread(NativeRunnable * runnable) :
					NativeThread(runnable), name(), mutex(), priority(NORMAL), thread(0)
				{
				}


				int UnixAbstractThread::priorityToNativePriority() {
					int pmin = sched_get_priority_min(SCHED_OTHER);
					int pmax = sched_get_priority_max(SCHED_OTHER);

					switch (priority) {
						case LOWEST:
							return pmin;
						case LOW:
							return pmin + (pmax - pmin) / 4;
						case NORMAL:
							return pmin + (pmax - pmin) / 2;
						case HIGH:
							return pmin + 3 * (pmax - pmin) / 4;
						case HIGHEST:
							return pmax;
						default:
							return pmin + (pmax - pmin) / 2;
					}
				}

				NativeString UnixAbstractThread::getName() {
					ScopedLock synchronize(mutex);
					return name;
				}

				void UnixAbstractThread::setName(NativeString& newName) {
					ScopedLock synchronize(mutex);
					name = newName;
				}

				Priority UnixAbstractThread::getPriority() {
					ScopedLock synchronize(mutex);
					return priority;
				}

				void UnixAbstractThread::setPriority(Priority newPriority) {
					ScopedLock synchronize(mutex);
					if (priority != newPriority) {
						priority = newPriority;
						if (isRunning()) {
							struct sched_param par;
							par.sched_priority = priorityToNativePriority();
#if defined(SOLARIS2)
							if (thr_setprio(thread, par.sched_priority)){
#else
							if (pthread_setschedparam(thread, SCHED_OTHER, &par)) { //TODO on AIX, Operation not permitted
#endif
								throw NativeException(className, "setPriority", SYSTEM_EXCEPTION, "cannot set thread priority");
							}
						}
					}
				}

				void UnixAbstractThread::yield() {
					sched_yield();
				}

				void UnixAbstractThread::suspend() {
					if (!isRunning()) {
						throw NativeException(className, "suspend", SYSTEM_EXCEPTION, "Thread is not running to suspend!");
					}
					int returnCode;
#if defined(_AIX)
					returnCode = pthread_suspend_np(thread);
#elif defined(SOLARIS2)
					returnCode = thr_suspend(thread);
#elif defined(Linux)
					returnCode = pthread_kill(thread, SIG_SUSPEND);
#endif
					if (returnCode){
						std::string message = "Failed to Suspend Thread ";
						message += name.getString();
						message += " Return Error Code = ";
						message += returnCode;

						throw NativeException(className, "suspend", SYSTEM_EXCEPTION, message);
					}
				}

				void UnixAbstractThread::resume() {
					if (!isRunning()) {
						throw NativeException(className, "resume", SYSTEM_EXCEPTION, "Thread is not running to resume!");
					}
					int returnCode;
#if defined(_AIX)
					returnCode = pthread_continue_np(thread);
#elif defined(SOLARIS2)
					returnCode = thr_continue(thread);
#elif defined(Linux)
					returnCode = pthread_kill(thread, SIG_RESUME);
#endif
					if (returnCode){
						std::string message = "Failed to Resume Thread ";
						message += name.getString();
						message += " Return Error Code = ";
						message += returnCode;

						throw NativeException(className, "resume", SYSTEM_EXCEPTION, message);
					}
				}


#if defined(SOLARIS2)
				int stackWalkCallBack(uintptr_t pc, int signo, void *data)
				{
					std::vector<NativeStackTraceElement> *stackTrace = reinterpret_cast<std::vector<NativeStackTraceElement> *>(data);
					Dl_info info;
					const char *filename;
					const char *functionname;
					unsigned int line;

					if (dladdr(reinterpret_cast<void*>(pc), &info) == 0){
						//printf("[0x%p]\n", pc);
					}
					else if (info.dli_fname!=NULL && info.dli_sname!=NULL){
						stackTrace->push_back(NativeStackTraceElement(NativeString(filename),NativeString(functionname),line));
					}
					else {
						//printf("%s' 0x%p [0x%p]\n",info.dli_fname, pc - reinterpret_cast<uintptr_t>(info.dli_fbase),pc);
					}

					return 0;
				}
#endif

				void UnixAbstractThread::getStackTrace(std::vector<NativeStackTraceElement> &stackTrace) {
#if defined(SOLARIS2)
					if (!isRunning() || thread != thr_self()){
#else
					if (!isRunning() || !pthread_equal(thread, pthread_self())){
#endif

						return;
					}

					stackTrace.clear();
#if defined(Linux)
					int j, nptrs;
					const int SIZE = 100;
					void *buffer[100];
					char **strings;

					nptrs = backtrace(buffer, SIZE);
					strings = backtrace_symbols(buffer, nptrs);

					for (j=0; j<nptrs; j++){
						stackTrace.push_back(NativeStackTraceElement(NativeString("unknown"),NativeString(strings[j]),0));
					}
#endif

#if defined(SOLARIS2)
					ucontext_t context;

					if (getcontext(&context) < 0){
						return;
					}

					walkcontext(&context, stackWalkCallBack, reinterpret_cast<void*>(&stackTrace));

#endif

				}
			}
		}
	}
}
