#include "jcpp/gc/ThreadInfo.h"

namespace jcpp {
	namespace gc {

		ThreadInfo::ThreadInfo(NativeThread* nativethread) : nativethread(nativethread), methodCallInfos(null), capacity(30), size(0) {
			methodCallInfos = new MethodCallInfo*[30];
		}

		void ThreadInfo::pushMethodCallInfo(MethodCallInfo* methodCallInfo) {
			if(size == capacity) {
				MethodCallInfo** newMethodCallInfos = new MethodCallInfo*[capacity + 30];
				for(jint i = 0; i < size; i++) {
					newMethodCallInfos[i] = methodCallInfos[i];
				}
				delete [] methodCallInfos;
				methodCallInfos = newMethodCallInfos;
				capacity += 30;
			}
			methodCallInfos[size++] = methodCallInfo;
		}

		void ThreadInfo::popMethodCallInfo() {
			size--;
		}

		jbool ThreadInfo::hasMethodCalls() {
			return size > 0;
		}

		jint ThreadInfo::getSize() {
			return size;
		}

		MethodCallInfo** ThreadInfo::getMethodCallInfos() {
			return methodCallInfos;
		}

		ThreadInfo::~ThreadInfo() {
			delete [] methodCallInfos;
		}

	}
}
