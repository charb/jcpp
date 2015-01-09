#include "jcpp/native/windows/library/WindowsLibrary.h"
#include "jcpp/native/api/NativeException.h"

using namespace jcpp::native::api;

namespace jcpp {
	namespace native {
		namespace windows {
			namespace library {
				NativeString WindowsLibrary::className("jcpp::native::windows::library::WindowsLibrary");

				WindowsLibrary::WindowsLibrary(const NativeString& path) : NativeLibrary(path) {
					hModuleDll = LoadLibrary(path.getString().c_str());
					if (!hModuleDll) {
						throw NativeException(className, "WindowsLibrary", SYSTEM_EXCEPTION, "Failed to Dynamically load: " + path, GetLastError());
					}
				}

				void* WindowsLibrary::getFunction(const NativeString& name) const{
					FARPROC procAddress = GetProcAddress(hModuleDll, name.getString().c_str());
					if (!procAddress) {
						throw NativeException(className, "getFunction", SYSTEM_EXCEPTION, "Failed to get the address of the exported method " + name +  " from the Dynamically loaded library " + path, GetLastError());
					}
					return procAddress;
				}

				WindowsLibrary::~WindowsLibrary(){
					if (hModuleDll) {
						FreeLibrary(hModuleDll);
						hModuleDll = NULL;
					}
				}
			}
		}
	}
}
