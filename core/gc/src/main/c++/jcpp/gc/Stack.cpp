#include "jcpp/gc/Stack.h"
#include "jcpp/native/api/NativeFactory.h"

using namespace jcpp::native::api;

namespace jcpp {
	namespace gc {

		Stack* Stack::stack = null;

		Stack::Stack() {
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
			threadInfo = threads[currentThread];
			if(threadInfo == null) {
				threadInfo = new ThreadInfo(currentThread);
				threads[currentThread] = threadInfo;
			}
			mutex->unlock();

			threadInfo->pushMethodCallInfo(methodCall);
		}

		void Stack::methodCallExiting() {
			NativeThread* currentThread = NativeFactory::getNativeThreadFactory()->currentThread();
			ThreadInfo* threadInfo = null;
			mutex->lock();
			threadInfo = threads[currentThread];
			mutex->unlock();

			if(threadInfo != null) {
				threadInfo->popMethodCallInfo();
				if(!threadInfo->hasMethodCalls()) {

					mutex->lock();
					threads.erase(currentThread);
					mutex->unlock();

					delete threadInfo;
					threadInfo = null;

				}
			}
		}

		/**
		 * Note: Do not synchronize the below method because we might have a dead lock between a suspended thread and the GC Thread
		 */
		void Stack::addRoot(TraverseContext* context) {
			for(std::map<NativeThread*, ThreadInfo*>::iterator it = threads.begin(); it != threads.end(); it++) {
				std::vector<MethodCallInfo*>* methodCallInfos = it->second->getMethodCallInfos();
				for(std::vector<MethodCallInfo*>::iterator mcIt = methodCallInfos->begin(); mcIt != methodCallInfos->end(); mcIt++) {
					context->addMethodCallInfo(*mcIt);
				}
			}
		}

		Stack::~Stack() {
			delete mutex;
		}

	}
}
