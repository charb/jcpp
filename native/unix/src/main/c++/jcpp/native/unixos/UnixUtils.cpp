#include "jcpp/native/unixos/UnixUtils.h"
#include "jcpp/native/api/NativeException.h"

#include <stdlib.h>
#include <errno.h>

using namespace jcpp::native::api;

extern char **environ;

namespace jcpp {
	namespace native {
		namespace unixos {

			jlong UnixUtils::getCurrentTimeMillis() {
				struct timeval tv;
				if (gettimeofday(&tv, NULL) != 0) {
					throw NativeException("jcpp::native::unixos::UnixUtils", "getCurrentTimeMillis", SYSTEM_EXCEPTION, "cannot get time of day!");
				}
				return (tv.tv_sec * 1000LL) + (tv.tv_usec / 1000LL);
			}

			void UnixUtils::getEnv(std::map<NativeString, NativeString>& env) {
				char * currentPtr = environ[0];
				int length = strlen(currentPtr);
				while (length > 0) {
					NativeString envKeyValue(currentPtr);
					int equalIndex = envKeyValue.indexOf('=');
					if (equalIndex >= 0) {
						env.insert(std::pair<NativeString, NativeString>(envKeyValue.substring(0, equalIndex), envKeyValue.substring(equalIndex + 1)));
					}
					currentPtr = currentPtr + length + 1;
					length = strlen(currentPtr);
				}
			}

			void UnixUtils::longToTimeval(struct timeval& tv, jlong millis) {
				jlong seconds = millis / 1000;
				tv.tv_sec = seconds;
				tv.tv_usec = (millis - (seconds * 1000)) * 1000;
			}

			jlong UnixUtils::timevalToLong(struct timeval tv) {
				return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
			}

			void UnixUtils::longToTimespec(struct timespec& tv, jlong millis) {
				jlong seconds = millis / 1000;
				tv.tv_sec = seconds;
				tv.tv_nsec = (millis - (seconds * 1000)) * 1000000;
			}

			jlong UnixUtils::timespecToLong(struct timespec& tv) {
				return (tv.tv_sec * 1000) + (tv.tv_nsec / 1000000);
			}

			// TODO check what jvm uses for sleeping
			void UnixUtils::sleep(jlong milliseconds) {
				int rc;
				do {
					struct timespec ts;
					struct timespec tsRem;
					UnixUtils::longToTimespec(ts, milliseconds);
					rc = nanosleep(&ts, &tsRem);

					if (rc < 0 && errno == EINTR) {
						milliseconds = UnixUtils::timespecToLong(tsRem);
					}
				} while (milliseconds > 0 && rc < 0 && errno == EINTR);
				if (rc < 0 && milliseconds > 0)
					throw NativeException("jcpp::native::unixos:UnixUtils", "sleep", SYSTEM_EXCEPTION, "Failed to Sleep");
			}

			void UnixUtils::handleLastSocketError(const NativeString& className, const NativeString& methodName, const NativeString& message) {
				handleLastSocketError(errno, className, methodName, message);
			}

			void UnixUtils::handleLastSocketError(const int err, const NativeString& className, const NativeString& methodName, const NativeString& message) {
				switch (err) {
					case EBADF:
						throw NativeException(className, methodName, SOCKET_EXCEPTION, "The socket argument is not a valid file descriptor: " + message, err);
					case ENOTSOCK:
						throw NativeException(className, methodName, SOCKET_EXCEPTION, "The descriptor socket is not a socket: " + message, err);
					case EPROTONOSUPPORT:
						throw NativeException(className, methodName, PROTOCOL_EXCEPTION, "The protocol or style is not supported by the namespace specified: " + message, err);
					case ENOPROTOOPT:
						throw NativeException(className, methodName, PROTOCOL_EXCEPTION, "The option name doesn't make sense for the given level: " + message, err);
					case EMFILE:
						throw NativeException(className, methodName, SOCKET_EXCEPTION, "The process already has too many file descriptors open: " + message, err);
					case ENFILE:
						throw NativeException(className, methodName, SYSTEM_EXCEPTION, "The system already has too many file descriptors open: " + message, err);
					case EACCES:
						throw NativeException(className, methodName, SOCKET_EXCEPTION, "The process does not have the privilege to create a socket of the specified style or protocol: " + message, err);
					case ENOBUFS:
						throw NativeException(className, methodName, OUT_OF_MEMORY_EXCEPTION, "The system ran out of internal buffer space: " + message, err);
					default:
						throw NativeException(className, methodName, SOCKET_EXCEPTION, message, err);
				}
			}

		}
	}
}

