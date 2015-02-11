#include "jcpp/gc/Stack.h"
#include "jcpp/native/api/NativeFactory.h"

using namespace jcpp::native::api;

namespace jcpp {
	namespace gc {

		Stack* Stack::stack = null;

		Stack::Stack() : threads(100, null) {
			mutex = NativeFactory::getNativeThreadFactory()->createNativeMutex();
		}

		Stack* Stack::getStack() {
			if(stack == null) {
				stack = new Stack();
			}
			return stack;
		}

		void Stack::methodCallStarted(MethodCallInfo* methodCall) {
			NativeThread* currentThread = NativeFactory::getNativeThreadFactory()->currentThread();

			ThreadInfo* threadInfo = null;
			mutex->lock();
			if(threads.size() + 1 < currentThread->getId()) {
				threads.resize(currentThread->getId() + 100, null);
			}
			threadInfo = threads[currentThread->getId()];
			if(threadInfo == null) {
				threadInfo = new ThreadInfo(currentThread);
				threads[currentThread->getId()] = threadInfo;
			}
			mutex->unlock();

			threadInfo->pushMethodCallInfo(methodCall);
		}

		void Stack::methodCallExiting() {
			NativeThread* currentThread = NativeFactory::getNativeThreadFactory()->currentThread();
			ThreadInfo* threadInfo = null;
			mutex->lock();
			threadInfo = threads[currentThread->getId()];
			mutex->unlock();

			if(threadInfo != null) {
				threadInfo->popMethodCallInfo();
			}
		}

		/**
		 * Note: Do not synchronize the below method because we might have a dead lock between a suspended thread and the GC Thread
		 */
		void Stack::addRoot(TraverseContext* context) {
			for(std::vector<ThreadInfo*>::iterator it = threads.begin(); it != threads.end(); it++) {
				if(*it) {
					std::vector<MethodCallInfo*>* methodCallInfos = (*it)->getMethodCallInfos();
					for(std::vector<MethodCallInfo*>::iterator mcIt = methodCallInfos->begin(); mcIt != methodCallInfos->end(); mcIt++) {
						context->addMethodCallInfo(*mcIt);
					}
				}
			}
		}

		Stack::~Stack() {
			delete mutex;
		}

	}
}
