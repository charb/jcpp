#include "jcpp/native/windows/WindowsUtils.h"
#include "jcpp/native/api/NativeException.h"

namespace jcpp {
	namespace native {
		namespace windows {

			jlong WindowsUtils::getCurrentTimeMillis() {
				FILETIME time;
				GetSystemTimeAsFileTime(&time);
				return WindowsUtils::fileTimeToJlong(time);
			}

			void WindowsUtils::getEnv(std::map<NativeString, NativeString>& env) {
				LPCH ptr = GetEnvironmentStrings();

				LPCH currentPtr = ptr;
				int length = strlen(currentPtr);
				while (length > 0) {
					NativeString envKeyValue(currentPtr);
					int equalIndex = envKeyValue.indexOf('=');
					env.insert(std::pair<NativeString, NativeString>(envKeyValue.substring(0, equalIndex), envKeyValue.substring(equalIndex + 1)));
					currentPtr = currentPtr + length + 1;
					length = strlen(currentPtr);
				}

				FreeEnvironmentStrings(ptr);
			}

			void WindowsUtils::longToTimeval(struct timeval& tv, jlong millis) {
				jlong seconds = millis / 1000;
				tv.tv_sec = seconds;
				tv.tv_usec = (millis - (seconds * 1000)) * 1000;
			}

			jlong WindowsUtils::timevalToLong(struct timeval tv) {
				return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
			}

			jlong WindowsUtils::fileTimeToJlong(FILETIME & time) {
				ULARGE_INTEGER epoch; // UNIX epoch (1970-01-01 00:00:00) expressed in Windows NT FILETIME
				epoch.u.LowPart = 0xD53E8000;
				epoch.u.HighPart = 0x019DB1DE;
				ULARGE_INTEGER ts;
				ts.u.LowPart = time.dwLowDateTime;
				ts.u.HighPart = time.dwHighDateTime;
				ts.QuadPart -= epoch.QuadPart;

				return (jlong) (ts.QuadPart / 10000);
			}

			void WindowsUtils::jlongToFileTime(jlong value, FILETIME & time) {
				ULARGE_INTEGER epoch; // UNIX epoch (1970-01-01 00:00:00) expressed in Windows NT FILETIME
				epoch.u.LowPart = 0xD53E8000;
				epoch.u.HighPart = 0x019DB1DE;

				ULARGE_INTEGER ts;
				ts.u.LowPart = value & (0xFFFFFFFF);
				ts.u.HighPart = (value >> 32) & (0xFFFFFFFF);
				ts.QuadPart *= 10000;
				ts.QuadPart += epoch.QuadPart;

				time.dwLowDateTime = ts.u.LowPart;
				time.dwHighDateTime = ts.u.HighPart;
			}

			void WindowsUtils::handleLastWinSockError(const NativeString& className, const NativeString& methodName, const NativeString& message) {
				handleLastWinSockError(WSAGetLastError(), className, methodName, message);
			}

			void WindowsUtils::handleLastWinSockError(const int err, const NativeString& className, const NativeString& methodName, const NativeString& message) {
				switch (err) {
					case WSA_INVALID_HANDLE:
						throw NativeException(className, methodName, SYSTEM_EXCEPTION, "Specified event object handle is invalid: " + message, err);
					case WSA_NOT_ENOUGH_MEMORY:
						throw NativeException(className, methodName, OUT_OF_MEMORY_EXCEPTION, "Insufficient memory available: " + message, err);
					case WSA_INVALID_PARAMETER:
						throw NativeException(className, methodName, ILLEGAL_ARGUMENT_EXCEPTION, "One or more parameters are invalid: " + message, err);
					case WSA_OPERATION_ABORTED:
						throw NativeException(className, methodName, PROTOCOL_EXCEPTION, "Overlapped operation aborted: " + message, err);
					case WSA_IO_INCOMPLETE:
						throw NativeException(className, methodName, IO_EXCEPTION, "Overlapped I/O event object not in signaled state: " + message, err);
					case WSAEBADF:
						throw NativeException(className, methodName, ILLEGAL_ARGUMENT_EXCEPTION, "File handle is not valid: " + message, err);
					case WSAEACCES:
						throw NativeException(className, methodName, SOCKET_EXCEPTION, "Permission denied: " + message, err);
					case WSAHOST_NOT_FOUND:
						throw NativeException(className, methodName, UNKNOWN_HOST_EXCEPTION, "Host not found: " + message, err);
					case WSATRY_AGAIN:
						throw NativeException(className, methodName, PROTOCOL_EXCEPTION, "Nonauthoritative host not found: " + message, err);
					case WSAELOOP:
						throw NativeException(className, methodName, PROTOCOL_EXCEPTION, "Cannot translate name: " + message, err);
					case WSAETIMEDOUT:
						throw NativeException(className, methodName, SOCKET_TIMEOUT_EXCEPTION, "Connection timed out: " + message, err);
					case WSAECONNREFUSED:
						throw NativeException(className, methodName, SOCKET_EXCEPTION, "Connection refused: " + message, err);
					case WSAEHOSTUNREACH:
					case WSAENETUNREACH:
						throw NativeException(className, methodName, SOCKET_EXCEPTION, "Host unreachable: " + message, err);
					case WSAENETDOWN:
						throw NativeException(className, methodName, SOCKET_EXCEPTION, "Network is down: " + message, err);
					case WSAEMFILE:
						throw NativeException(className, methodName, SOCKET_EXCEPTION, "Too many open files (no more socket descriptors): " + message, err);
					case WSAEWOULDBLOCK:
						throw NativeException(className, methodName, SOCKET_EXCEPTION, "Resource temporarily unavailable: " + message, err);
					case WSAEADDRINUSE:
						throw NativeException(className, methodName, BIND_EXCEPTION, "Address already in use: " + message, err);
					case WSAEADDRNOTAVAIL:
						throw NativeException(className, methodName, BIND_EXCEPTION, "Cannot assign requested address: " + message, err);
					case WSAENOBUFS:
						throw NativeException(className, methodName, SOCKET_EXCEPTION, "No buffer space is available, the socket cannot be created: " + message, err);
					case WSAENETRESET:
						throw NativeException(className, methodName, IO_EXCEPTION, "The connection has been broken due to keep-alive activity that detected a failure while the operation was in progress: " + message, err);
					case WSAECONNRESET:
						throw NativeException(className, methodName, SOCKET_EXCEPTION, "Connection reset: " + message, err);
					case WSAEMSGSIZE:
						throw NativeException(className, methodName, IO_EXCEPTION, "Message too long. Increase Buffer Size: " + message, err);
					default:
						throw NativeException(className, methodName, SOCKET_EXCEPTION, message, err);
				}
			}

		}
	}
}
