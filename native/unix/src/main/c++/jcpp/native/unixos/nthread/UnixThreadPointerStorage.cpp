#include "jcpp/native/unixos/nthread/UnixThreadPointerStorage.h"
#include "jcpp/native/api/NativeException.h"

namespace jcpp {
	namespace native {
		namespace unixos {
			namespace nthread {

				NativeString UnixThreadPointerStorage::className("jcpp::native::unixos::thread::UnixThreadPointerStorage");
				UnixThreadPointerStorage UnixThreadPointerStorage::instance;

				UnixThreadPointerStorage::UnixThreadPointerStorage() {
					if (pthread_key_create(&key, NULL)) {
						throw NativeException(className, "UnixThreadPointerStorage()", SYSTEM_EXCEPTION, "cannot allocate thread context key");
					}
				}

				UnixThreadPointerStorage::~UnixThreadPointerStorage() {
					pthread_key_delete(key);
				}

				UnixThreadPointerStorage* UnixThreadPointerStorage::getInstance() {
					return &instance;
				}

				UnixThread * UnixThreadPointerStorage::get() const {
					return reinterpret_cast<UnixThread*>(pthread_getspecific(key));
				}

				void UnixThreadPointerStorage::set(UnixThread * pthread) {
					pthread_setspecific(key, pthread);
				}

			}
		}
	}
}

