#ifndef JCPP_NATIVE_WINDOWS_LIBRARY_WINDOWSLIBRARY
#define JCPP_NATIVE_WINDOWS_LIBRARY_WINDOWSLIBRARY

#include "jcpp/native/api/library/NativeLibrary.h"
#include "jcpp/native/windows/WindowsInclude.h"

using namespace jcpp::native::api::library;

namespace jcpp {
	namespace native {
		namespace windows {
			namespace library {
				class JCPP_EXPORT WindowsLibrary: public NativeLibrary {

				private:
					static NativeString className;

					HMODULE hModuleDll;

				public:
					WindowsLibrary(const NativeString& path);

					virtual void* getFunction(const NativeString& name) const;

					virtual ~WindowsLibrary();
				};
			}
		}
	}
}

#endif
