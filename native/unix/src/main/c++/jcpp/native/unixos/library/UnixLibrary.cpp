#include "jcpp/native/unixos/library/UnixLibrary.h"
#include "jcpp/native/api/NativeException.h"
#include "jcpp/native/api/nthread/ScopedLock.h"
#include <dlfcn.h>

using namespace jcpp::native::api;
using jcpp::native::api::nthread::ScopedLock;

namespace jcpp {
	namespace native {
		namespace unixos {
			namespace library {
				NativeString UnixLibrary::className("jcpp::native::unixos::library::UnixLibrary");

				UnixLibrary::UnixLibrary(UnixMutex * errorMutex, const NativeString& path) : NativeLibrary(path), errorMutex(errorMutex) {
					ScopedLock synchronize(*errorMutex);
					handle = dlopen(path.getString().c_str(), RTLD_LOCAL | RTLD_LAZY);
					if(!handle) {
						throw NativeException(className, "UnixLibrary", SYSTEM_EXCEPTION, "Failed to Dynamically load: " + path + ". Error = " + dlerror());
					}
				}

				void* UnixLibrary::getFunction(const NativeString& name) const{
					ScopedLock synchronize(*errorMutex);
					void* symbolAddress = dlsym(handle, name.getString().c_str());
					if(!symbolAddress) {
						throw NativeException(className, "getFunction", SYSTEM_EXCEPTION, "Failed to get the address of the exported method " + name +  " from the Dynamically loaded library " + path + ". Error = " + dlerror());
					}
					return symbolAddress;
				}

				UnixLibrary::~UnixLibrary(){
					if(handle) {
						dlclose(handle);
						handle = null;
					}
				}
			}
		}
	}
}
