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
			static const jint DEFAULT_CAPACITY = 30;

			NativeThread* nativethread;

			MethodCallInfo** methodCallInfos;
			jint capacity;
			jint size;

		public:
			ThreadInfo(NativeThread* nativethread);

			void pushMethodCallInfo(MethodCallInfo* methodCallInfo);

			void popMethodCallInfo();

			MethodCallInfo** getMethodCallInfos();

			jbool hasMethodCalls();

			jint getSize();

			virtual ~ThreadInfo();

		};

	}
}

#endif
