#ifndef JCPP_NATIVE_API_FILE_NATIVEEXCEPTION
#define JCPP_NATIVE_API_FILE_NATIVEEXCEPTION

#include "jcpp/native/api/NativeString.h"

namespace jcpp {
	namespace native {
		namespace api {

			enum ExceptionType {
				UNKNOWN_EXCEPTION,
				NULL_POINTER_EXCEPTION,
				ILLEGAL_ARGUMENT_EXCEPTION,
				OUT_OF_BOUND_EXCEPTION,
				ILLEGAL_STATE_EXCEPTION,
				SYSTEM_EXCEPTION,
				IO_EXCEPTION,
				FILE_EXCEPTION,
				FILE_EXISTS_EXCEPTION,
				FILE_NOT_FOUND_EXCEPTION,
				FILE_READ_ONLY_EXCEPTION,
				FILE_ACCESS_DENIED_EXCEPTION,
				FILE_CREATE_EXCEPTION,
				FILE_OPEN_EXCEPTION,
				FILE_WRITE_EXCEPTION,
				FILE_READ_EXCEPTION,
				PATH_NOT_FOUND_EXCEPTION,
				PATH_SYNTAX_EXCEPTION,
				INTERRUPTED_EXCEPTION,
				UNKNOWN_HOST_EXCEPTION,
				SOCKET_EXCEPTION,
				SOCKET_TIMEOUT_EXCEPTION,
				OUT_OF_MEMORY_EXCEPTION,
				BIND_EXCEPTION,
				PROTOCOL_EXCEPTION,
				CONNECT_EXCEPTION
			};

			class JCPP_EXPORT NativeException {
			protected:
				jint errorCode;
				ExceptionType type;
				NativeString message;
				NativeString className;
				NativeString methodName;
			public:
				NativeException(const NativeString& className, const NativeString& methodName);

				NativeException(const NativeString& className, const NativeString& methodName, const ExceptionType type, const NativeString& message);

				NativeException(const NativeString& className, const NativeString& methodName, const ExceptionType type, const NativeString& message, const jint errorCode);

				NativeString getClassName() const;
				NativeString getMethodName() const;
				NativeString getMessage() const;
				ExceptionType getType() const;
				NativeString getTypeString() const;
				jint getErrorCode() const;
			};

		}
	}
}

#endif
