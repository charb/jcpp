#ifndef JCPP_NATIVE_API_THREAD_NATIVESTACKTRACEELEMENT
#define JCPP_NATIVE_API_THREAD_NATIVESTACKTRACEELEMENT

#include "jcpp/native/api/NativeString.h"

namespace jcpp {
	namespace native {
		namespace api {
			namespace nthread {

			class JCPP_EXPORT NativeStackTraceElement {
			private:
				NativeString fileName;
				NativeString methodName;
				jint lineNumber;

			public:
				NativeStackTraceElement(const NativeString &fileName, const NativeString &methodName, jint lineNumber);
				NativeStackTraceElement(const NativeStackTraceElement &stackTraceElement);
				virtual ~NativeStackTraceElement();


				NativeString getFileName() const;


				NativeString getMethodName() const;


				jint getLineNumber() const;

			};

			}
		}
	}
}

#endif
