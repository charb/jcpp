#include "jcpp/gc/ThreadInfo.h"

namespace jcpp {
	namespace gc {

		ThreadInfo::ThreadInfo(NativeThread* nativethread) : nativethread(nativethread), methodCallInfos(null), capacity(DEFAULT_CAPACITY), size(0) {
			methodCallInfos = new MethodCallInfo*[DEFAULT_CAPACITY];
		}

		void ThreadInfo::pushMethodCallInfo(MethodCallInfo* methodCallInfo) {
			if(size == capacity) {
				MethodCallInfo** newMethodCallInfos = new MethodCallInfo*[capacity + DEFAULT_CAPACITY];
				for(jint i = 0; i < size; i++) {
					newMethodCallInfos[i] = methodCallInfos[i];
				}
				delete [] methodCallInfos;
				methodCallInfos = newMethodCallInfos;
				capacity += DEFAULT_CAPACITY;
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
