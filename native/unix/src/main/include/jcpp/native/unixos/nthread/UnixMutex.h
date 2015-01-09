#ifndef JCPP_NATIVE_UNIXOS_THREAD_UNIXMUTEX
#define JCPP_NATIVE_UNIXOS_THREAD_UNIXMUTEX

#include "jcpp/native/api/nthread/NativeMutex.h"
#include "jcpp/native/api/NativeString.h"

using namespace jcpp::native::api;
using namespace jcpp::native::api::nthread;

namespace jcpp {
	namespace native {
		namespace unixos {
			namespace nthread {

				class UnixCondition;

				class JCPP_EXPORT UnixMutex: public NativeMutex {

					friend class UnixCondition;

				private:
					static NativeString className;

					pthread_mutex_t _mutex;

					UnixMutex(const UnixMutex&);
					UnixMutex& operator =(const UnixMutex&);

				protected:
					pthread_mutex_t * getPthreadMutex();

				public:
					UnixMutex();
					virtual ~UnixMutex();

					virtual void lock();
					virtual jbool tryLock();
					virtual jbool tryLock(jlong milliseconds);
					virtual void unlock();

				};

			}
		}
	}
}

#endif

