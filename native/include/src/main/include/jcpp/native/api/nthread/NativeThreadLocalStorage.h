#ifndef JCPP_NATIVE_API_THREAD_NATIVETHREADLOCALSTORAGE
#define JCPP_NATIVE_API_THREAD_NATIVETHREADLOCALSTORAGE

#include "jcpp/native/api/NativeInclude.h"
#include <map>

namespace jcpp {
	namespace native {
		namespace api {
			namespace nthread {

				//~ -------------------------------------------
				//~ NativeThreadLocalStorageSlot
				//~ -------------------------------------------

				class JCPP_EXPORT NativeThreadLocalStorageSlot {
				private:
					void * value;

					NativeThreadLocalStorageSlot(const NativeThreadLocalStorageSlot&);
					NativeThreadLocalStorageSlot& operator =(const NativeThreadLocalStorageSlot&);

				public:

					NativeThreadLocalStorageSlot();
					~NativeThreadLocalStorageSlot();

					void* & getValue();

				};

				//~ -------------------------------------------
				//~ NativeThreadLocalStorage
				//~ -------------------------------------------

				class NativeThread;

				class JCPP_EXPORT NativeThreadLocalStorage {

				private:
					std::map<const void*, NativeThreadLocalStorageSlot *> slots;

					NativeThreadLocalStorage(const NativeThreadLocalStorage&);
					NativeThreadLocalStorage& operator =(const NativeThreadLocalStorage&);

				public:
					NativeThreadLocalStorage();
					~NativeThreadLocalStorage();

					static NativeThreadLocalStorage* current();

					NativeThreadLocalStorageSlot*& get(const void* key);
					void clear();

				};

			}
		}
	}

}

#endif
