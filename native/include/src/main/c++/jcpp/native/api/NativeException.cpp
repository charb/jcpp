#include "jcpp/native/api/NativeException.h"

namespace jcpp {
	namespace native {
		namespace api {

			NativeException::NativeException(const NativeString& className, const NativeString& methodName) :
				errorCode(-1), type(UNKNOWN_EXCEPTION), message(), className(className), methodName(methodName)   {
			}

			NativeException::NativeException(const NativeString& className, const NativeString& methodName, const ExceptionType type, const NativeString& message) :
				errorCode(-1), type(type), message(message), className(className), methodName(methodName)  {
			}

			NativeException::NativeException(const NativeString& className, const NativeString& methodName, const ExceptionType type, const NativeString& message, const jint errorCode) :
				 errorCode(errorCode), type(type), message(message), className(className), methodName(methodName) {
			}

			NativeString NativeException::getMethodName() const {
				return methodName;
			}

			NativeString NativeException::getClassName() const {
				return className;
			}

			NativeString NativeException::getMessage() const {
				return message;
			}

			ExceptionType NativeException::getType() const {
				return type;
			}

			NativeString NativeException::getTypeString() const {
				switch(type) {
					case UNKNOWN_EXCEPTION:
						return NativeString("UNKNOWN_EXCEPTION");
					case NULL_POINTER_EXCEPTION:
						return NativeString("NULL_POINTER_EXCEPTION");
					case ILLEGAL_ARGUMENT_EXCEPTION:
						return NativeString("ILLEGAL_ARGUMENT_EXCEPTION");
					case OUT_OF_BOUND_EXCEPTION:
						return NativeString("OUT_OF_BOUND_EXCEPTION");
					case ILLEGAL_STATE_EXCEPTION:
						return NativeString("ILLEGAL_STATE_EXCEPTION");
					case SYSTEM_EXCEPTION:
						return NativeString("SYSTEM_EXCEPTION");
					case IO_EXCEPTION:
						return NativeString("IO_EXCEPTION");
					case FILE_EXCEPTION:
						return NativeString("FILE_EXCEPTION");
					case FILE_EXISTS_EXCEPTION:
						return NativeString("FILE_EXISTS_EXCEPTION");
					case FILE_NOT_FOUND_EXCEPTION:
						return NativeString("FILE_NOT_FOUND_EXCEPTION");
					case FILE_READ_ONLY_EXCEPTION:
						return NativeString("FILE_READ_ONLY_EXCEPTION");
					case FILE_ACCESS_DENIED_EXCEPTION:
						return NativeString("FILE_ACCESS_DENIED_EXCEPTION");
					case FILE_CREATE_EXCEPTION:
						return NativeString("FILE_CREATE_EXCEPTION");
					case FILE_OPEN_EXCEPTION:
						return NativeString("FILE_OPEN_EXCEPTION");
					case FILE_WRITE_EXCEPTION:
						return NativeString("FILE_WRITE_EXCEPTION");
					case FILE_READ_EXCEPTION:
						return NativeString("FILE_READ_EXCEPTION");
					case PATH_NOT_FOUND_EXCEPTION:
						return NativeString("PATH_NOT_FOUND_EXCEPTION");
					case PATH_SYNTAX_EXCEPTION:
						return NativeString("PATH_SYNTAX_EXCEPTION");
					case INTERRUPTED_EXCEPTION:
						return NativeString("INTERRUPTED_EXCEPTION");
					case UNKNOWN_HOST_EXCEPTION:
						return NativeString("UNKNOWN_HOST_EXCEPTION");
					case SOCKET_EXCEPTION:
						return NativeString("SOCKET_EXCEPTION");
					case SOCKET_TIMEOUT_EXCEPTION:
						return NativeString("SOCKET_TIMEOUT_EXCEPTION");
					case OUT_OF_MEMORY_EXCEPTION:
						return NativeString("OUT_OF_MEMORY_EXCEPTION");
					case BIND_EXCEPTION:
						return NativeString("BIND_EXCEPTION");
					case PROTOCOL_EXCEPTION:
						return NativeString("PROTOCOL_EXCEPTION");
					case CONNECT_EXCEPTION:
						return NativeString("CONNECT_EXCEPTION");
					default:
						return NativeString("UNKNOWN_EXCEPTION");
				}
			}

			jint NativeException::getErrorCode() const {
				return errorCode;
			}

		}
	}
}
