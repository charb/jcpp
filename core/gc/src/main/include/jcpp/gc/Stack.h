#ifndef JCPP_GC_STACK_H
#define JCPP_GC_STACK_H

#include "jcpp/native/api/NativeInclude.h"
#include "jcpp/gc/ThreadInfo.h"
#include "jcpp/gc/TraverseContext.h"
#include "jcpp/native/api/nthread/NativeMutex.h"
#include <vector>

using namespace jcpp::native::api::nthread;

namespace jcpp {
	namespace gc {

		class JCPP_EXPORT Stack {
		private:
			static Stack* stack;

			NativeMutex* mutex;
			std::vector<ThreadInfo*> threads;

			Stack();
		public:
			static Stack* getStack();

			void methodCallStarted(MethodCallInfo* methodCall);

			void methodCallExiting();

			void addRoot(TraverseContext* context);

			virtual ~Stack();
		};

	}
}

#endif
