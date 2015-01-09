#ifndef JCPP_GC_DESTRUCTOR_THREAD_H
#define JCPP_GC_DESTRUCTOR_THREAD_H

#include "jcpp/native/api/nthread/NativeThread.h"
#include "jcpp/native/api/nthread/NativeCondition.h"
#include "jcpp/gc/TraverseContext.h"
#include "jcpp/gc/Heap.h"
#include <set>
#include <queue>

using namespace jcpp::native::api::nthread;

namespace jcpp {
	namespace gc {

		class JCPP_EXPORT DestructorThread : public NativeRunnable {
		private:

			Heap* heap;
			NativeMutex* setsMutex;
			NativeMutex* conditionMutex;
			NativeCondition* condition;
			NativeThread* nativeThread;
			std::queue<std::set<jlong>*> addressSetsToDestroy;
			jbool shutdownFlagged;
			jbool conditionNotified;

			void destroy(std::set<jlong>* addressesToDelete);
		public:
			DestructorThread(Heap* heap);

			NativeThread* getNativeThread();

			void start();

			void shutdown();

			void addSetToDestroy(std::set<jlong>* addressesToDelete);

			void run();

			virtual ~DestructorThread();
		};

	}
}

#endif
