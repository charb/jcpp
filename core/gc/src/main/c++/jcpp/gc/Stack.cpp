#include "jcpp/gc/Stack.h"
#include "jcpp/native/api/NativeFactory.h"
#include <vector>

using namespace jcpp::native::api;

namespace jcpp {
	namespace gc {

		Stack* Stack::stack = null;

		Stack::Stack() {
		}

		Stack* Stack::getStack() {
			if(stack == null) {
				stack = new Stack();
			}
			return stack;
		}

		void Stack::methodCallStarted(MethodCallInfo* methodCall) {
			NativeThread* currentThread = NativeFactory::getNativeThreadFactory()->currentThread();
			ThreadInfo* threadInfo = reinterpret_cast<ThreadInfo*>(currentThread->getGcThreadInfo());
			if(threadInfo == null) {
				threadInfo = new ThreadInfo(currentThread);
				currentThread->setGcThreadInfo(reinterpret_cast<void*>(threadInfo));
			}
			threadInfo->pushMethodCallInfo(methodCall);
		}

		void Stack::methodCallExiting() {
			NativeThread* currentThread = NativeFactory::getNativeThreadFactory()->currentThread();
			ThreadInfo* threadInfo =  reinterpret_cast<ThreadInfo*>(currentThread->getGcThreadInfo());
			if(threadInfo != null) {
				threadInfo->popMethodCallInfo();
			}
		}

		/**
		 * Note: Do not synchronize the below method because we might have a dead lock between a suspended thread and the GC Thread
		 */
		void Stack::addRoot(TraverseContext* context) {
			std::vector<NativeThread*> threads;
			NativeFactory::getNativeThreadFactory()->getAllThreads(threads);
			for(std::vector<NativeThread*>::iterator it = threads.begin(); it != threads.end(); it++) {
				ThreadInfo* threadInfo = (ThreadInfo*)(*it)->getGcThreadInfo();
				if(threadInfo && threadInfo->hasMethodCalls()) {
					MethodCallInfo** methodCallInfos = threadInfo->getMethodCallInfos();
					for(jint i = 0; i < threadInfo->getSize(); i++) {
						context->addMethodCallInfo(methodCallInfos[i]);
					}
				}
			}
		}

		Stack::~Stack() {
		}

	}
}
