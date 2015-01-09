#ifndef JCPP_NATIVE_API_THREAD_NATIVEMUTEX
#define JCPP_NATIVE_API_THREAD_NATIVEMUTEX

#include "jcpp/native/api/NativeInclude.h"

namespace jcpp {
	namespace native {
		namespace api {
			namespace nthread {

				class NativeMutexListener;

				class JCPP_EXPORT NativeMutex {

				private:
					NativeMutex(const NativeMutex&);
					NativeMutex& operator =(const NativeMutex&);

				protected:
					NativeMutexListener * listener;

					NativeMutex();

					NativeMutexListener * getListener();
					void setListener(NativeMutexListener * listener);
				public:
					virtual ~NativeMutex();

					virtual void lock() = 0;
					virtual jbool tryLock() = 0;
					virtual jbool tryLock(jlong milliseconds) = 0;
					virtual void unlock() = 0;

				};

				// Internal NativeMutexListener Interface

				class JCPP_EXPORT NativeMutexListener {

				private:
					NativeMutexListener(const NativeMutexListener&);
					NativeMutexListener& operator =(const NativeMutexListener&);

				protected:
					NativeMutexListener();

				public:
					virtual ~NativeMutexListener();

					virtual void mutexLocked(NativeMutex * mutex) = 0;
					virtual void mutexUnlock(NativeMutex * mutex) = 0;

				};

			}
		}
	}

}

#endif
