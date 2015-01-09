#include "jcpp/gc/ThreadInfo.h"

namespace jcpp {
	namespace gc {

		ThreadInfo::ThreadInfo(NativeThread* nativethread) : nativethread(nativethread), methodCallInfos() {
		}

		void ThreadInfo::pushMethodCallInfo(MethodCallInfo* methodCallInfo) {
			methodCallInfos.push_back(methodCallInfo);
		}

		void ThreadInfo::popMethodCallInfo() {
			methodCallInfos.pop_back();
		}

		jbool ThreadInfo::hasMethodCalls() {
			return methodCallInfos.size() > 0;
		}

		std::vector<MethodCallInfo*>* ThreadInfo::getMethodCallInfos() {
			return &methodCallInfos;
		}

		ThreadInfo::~ThreadInfo() {
		}

	}
}
