#ifndef JCPP_GC_THREADINFO_H
#define JCPP_GC_THREADINFO_H

#include "jcpp/native/api/NativeInclude.h"
#include "jcpp/gc/info/MethodCallInfo.h"
#include "jcpp/native/api/nthread/NativeThread.h"
#include "jcpp/gc/TraverseContext.h"
#include <vector>

using namespace jcpp::native::api::nthread;
using namespace jcpp::gc::info;

namespace jcpp {
	namespace gc {

		class JCPP_EXPORT ThreadInfo {

		private:
			NativeThread* nativethread;

			std::vector<MethodCallInfo*> methodCallInfos;
		public:
			ThreadInfo(NativeThread* nativethread);

			void pushMethodCallInfo(MethodCallInfo* methodCallInfo);

			void popMethodCallInfo();

			std::vector<MethodCallInfo*>* getMethodCallInfos();

			jbool hasMethodCalls();

			virtual ~ThreadInfo();

		};

	}
}

#endif
