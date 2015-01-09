#ifndef JCPP_NATIVE_UNIXOS_THREAD_UNIXTHREADPOINTERSTORAGE
#define JCPP_NATIVE_UNIXOS_THREAD_UNIXTHREADPOINTERSTORAGE

#include "jcpp/native/api/NativeString.h"
#include <pthread.h>

using namespace jcpp::native::api;

namespace jcpp {
	namespace native {
		namespace unixos {
			namespace nthread {

				class UnixThread;

				class JCPP_EXPORT UnixThreadPointerStorage {

				private:
					static UnixThreadPointerStorage instance;
					static NativeString className;

					pthread_key_t key;

					UnixThreadPointerStorage();
					UnixThreadPointerStorage(const UnixThreadPointerStorage&);
					UnixThreadPointerStorage& operator =(const UnixThreadPointerStorage&);

				public:
					~UnixThreadPointerStorage();

					static UnixThreadPointerStorage* getInstance();

					UnixThread * get() const;
					void set(UnixThread * pthread);

				};
			}
		}
	}

}

#endif
