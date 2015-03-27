#ifndef JCPP_GC_STACK_H
#define JCPP_GC_STACK_H

#include "jcpp/native/api/NativeInclude.h"
#include "jcpp/gc/ThreadInfo.h"
#include "jcpp/gc/TraverseContext.h"
#include "jcpp/native/api/nthread/NativeMutex.h"
#include "jcpp/gc/visitor/IMethodCallVisitor.h"

using namespace jcpp::gc;
using namespace jcpp::native::api::nthread;
using namespace jcpp::gc::visitor;

namespace jcpp {
	namespace gc {

		class GarbageCollector;

		class JCPP_EXPORT Stack {
			friend class GarbageCollector;
		private:
			static Stack* stack;

			Stack();

			void acceptMethodCallVisitor(IMethodCallVisitor *v);
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
