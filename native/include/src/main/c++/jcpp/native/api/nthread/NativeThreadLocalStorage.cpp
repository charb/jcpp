#include "jcpp/native/api/nthread/NativeThreadLocalStorage.h"
#include "jcpp/native/api/nthread/NativeThreadFactory.h"

namespace jcpp {
	namespace native {
		namespace api {
			namespace nthread {

				NativeThreadLocalStorageSlot::NativeThreadLocalStorageSlot() :
						value(null) {
				}

				NativeThreadLocalStorageSlot::~NativeThreadLocalStorageSlot() {
				}

				void* & NativeThreadLocalStorageSlot::getValue() {
					return value;
				}

				NativeThreadLocalStorage::NativeThreadLocalStorage() :
						slots() {
				}

				NativeThreadLocalStorage::~NativeThreadLocalStorage() {
					clear();
				}

				NativeThreadLocalStorage* NativeThreadLocalStorage::current() {
					return NativeThreadFactory::getInstance()->currentThread()->getStorage();
				}

				NativeThreadLocalStorageSlot*& NativeThreadLocalStorage::get(const void* key) {
					std::map<const void*, NativeThreadLocalStorageSlot *>::iterator it = slots.find(key);
					if (it == slots.end())
						return slots.insert(std::map<const void*, NativeThreadLocalStorageSlot *>::value_type(key, reinterpret_cast<NativeThreadLocalStorageSlot*>(null))).first->second;
					else
						return it->second;
				}

				void NativeThreadLocalStorage::clear() {
					for (std::map<const void*, NativeThreadLocalStorageSlot *>::iterator it = slots.begin(); it != slots.end(); ++it) {
						if (it->second) {
							delete it->second;
						}
					}
					slots.clear();
				}

			}
		}
	}

}
