#include "jcpp/native/api/nthread/NativeStackTraceElement.h"

namespace jcpp {
	namespace native {
		namespace api {
			namespace nthread {

				NativeStackTraceElement::NativeStackTraceElement(const NativeString &fileName, const NativeString &methodName, jint lineNumber) :
						fileName(fileName), methodName(methodName), lineNumber(lineNumber)
				{
				}

				NativeStackTraceElement::NativeStackTraceElement(const NativeStackTraceElement &stackTraceElement) :
						fileName(stackTraceElement.fileName), methodName(stackTraceElement.methodName), lineNumber(stackTraceElement.lineNumber)
				{
				}

				NativeStackTraceElement::~NativeStackTraceElement()
				{
				}


				NativeString NativeStackTraceElement::getFileName() const {
					return fileName;
				}

				NativeString NativeStackTraceElement::getMethodName() const {
					return methodName;
				}

				jint NativeStackTraceElement::getLineNumber() const {
					return lineNumber;
				}

			}
		}
	}
}
