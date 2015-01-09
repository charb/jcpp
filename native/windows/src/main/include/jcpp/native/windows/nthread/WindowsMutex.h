#ifndef JCPP_NATIVE_WINDOWS_THREAD_WINDOWSMUTEX
#define JCPP_NATIVE_WINDOWS_THREAD_WINDOWSMUTEX

#include "jcpp/native/api/nthread/NativeMutex.h"
#include "jcpp/native/api/NativeString.h"
#include "jcpp/native/windows/WindowsInclude.h"

using namespace jcpp::native::api;
using namespace jcpp::native::api::nthread;

namespace jcpp {
	namespace native {
		namespace windows {
			namespace nthread {

				class WindowsCondition;

				class JCPP_EXPORT WindowsMutex: public NativeMutex {

					friend WindowsCondition;

				private:
					static NativeString className;

					CRITICAL_SECTION _cs;

					WindowsMutex(const WindowsMutex&);
					WindowsMutex& operator =(const WindowsMutex&);

				public:
					WindowsMutex();
					virtual ~WindowsMutex();

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
