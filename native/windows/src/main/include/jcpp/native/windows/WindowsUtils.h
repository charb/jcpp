#ifndef JCPP_NATIVE_WINDOWS_WINDOWSUTILS
#define JCPP_NATIVE_WINDOWS_WINDOWSUTILS

#include "jcpp/native/api/NativeInclude.h"
#include "jcpp/native/api/NativeString.h"
#include "jcpp/native/windows/WindowsInclude.h"

#include <winsock2.h>
#include <map>

using namespace jcpp::native::api;

namespace jcpp {
	namespace native {
		namespace windows {

			class JCPP_EXPORT WindowsUtils {
			public:
				static jlong getCurrentTimeMillis();

				static void getEnv(std::map<NativeString, NativeString>& env);

				static void longToTimeval(struct timeval& tv, jlong millis);

				static jlong timevalToLong(struct timeval tv);

				static jlong fileTimeToJlong(FILETIME & time);

				static void jlongToFileTime(jlong value, FILETIME & time);

				static void handleLastWinSockError(const NativeString& className, const NativeString& methodName, const NativeString& message);

				static void handleLastWinSockError(const int errorCode, const NativeString& className, const NativeString& methodName, const NativeString& message);
			};
		}
	}
}

#endif
