#ifndef JCPP_NATIVE_WINDOWS_THREAD_WINDOWSTHREADPOINTERSTORAGE
#define JCPP_NATIVE_WINDOWS_THREAD_WINDOWSTHREADPOINTERSTORAGE

#include "jcpp/native/api/NativeString.h"
#include "jcpp/native/windows/WindowsInclude.h"

using namespace jcpp::native::api;

namespace jcpp {
	namespace native {
		namespace windows {
			namespace nthread {

				class WindowsThread;

				class JCPP_EXPORT WindowsThreadPointerStorage {

				private:
					static WindowsThreadPointerStorage instance;
					static NativeString className;

					DWORD slot;

					WindowsThreadPointerStorage();
					WindowsThreadPointerStorage(const WindowsThreadPointerStorage&);
					WindowsThreadPointerStorage& operator =(const WindowsThreadPointerStorage&);

				public:
					~WindowsThreadPointerStorage();

					static WindowsThreadPointerStorage* getInstance();

					WindowsThread * get() const;
					void set(WindowsThread * pthread);

				};
			}
		}
	}

}

#endif
