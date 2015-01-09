#ifndef JCPP_NATIVE_UNIXOS_UNIXUTILS
#define JCPP_NATIVE_UNIXOS_UNIXUTILS

#include "jcpp/native/api/NativeString.h"
#include <sys/time.h>
#include <map>
#include <string.h>

using namespace jcpp::native::api;

/**
 * EINTR_RETRY is used to retry method call that get interrupted by signal interrupts
 *
 * EINTR_RETRY : define the result field
 * EINTR_RETRY_R : needs the result field to be defined
 * EINTR_RETRY_RV : needs the result field and fail value to be defined
 *
 */

#define EINTR_RETRY(CODE) 						\
	int result = 0;								\
	while (true) { 								\
		result = CODE;		 					\
		if (result != -1 || errno != EINTR) { 	\
			break; 								\
		} 										\
	}


#define EINTR_RETRY_R(RESULT_NAME, CODE) 			\
	while (true) { 									\
		RESULT_NAME = CODE;		 					\
		if (RESULT_NAME != -1 || errno != EINTR) { 	\
			break; 									\
		} 											\
	}

#define EINTR_RETRY_RV(RESULT_NAME, FAIL_VALUE, CODE)		\
	while (true) { 											\
		RESULT_NAME = CODE;		 							\
		if (RESULT_NAME != FAIL_VALUE || errno != EINTR) { 	\
			break; 											\
		} 													\
	}

namespace jcpp {
	namespace native {
		namespace unixos {

			class JCPP_EXPORT UnixUtils {
			public:
				static void sleep(jlong milliseconds);
				static jlong getCurrentTimeMillis();
				static void getEnv(std::map<NativeString, NativeString>& env);

				static void longToTimeval(struct timeval& tv, jlong millis);
				static jlong timevalToLong(struct timeval tv);

				static void longToTimespec(struct timespec& tv, jlong millis);
				static jlong timespecToLong(struct timespec& tv);

				static void handleLastSocketError(const NativeString& className, const NativeString& methodName, const NativeString& message);
				static void handleLastSocketError(const int err, const NativeString& className, const NativeString& methodName, const NativeString& message);

			};
		}
	}
}

#endif
