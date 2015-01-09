#ifndef JCPP_GC_GARBAGE_COLLECTOR_H
#define JCPP_GC_GARBAGE_COLLECTOR_H

#include "jcpp/native/api/NativeInclude.h"
#include "jcpp/gc/Stack.h"
#include "jcpp/gc/Heap.h"
#include "jcpp/gc/DestructorThread.h"
#include "jcpp/native/api/nthread/NativeMutex.h"

using namespace jcpp::native::api::nthread;

namespace jcpp {
	namespace gc {

		class JCPP_EXPORT GarbageCollector {
		private:
			static GarbageCollector* garbageCollector;

			Stack* stack;
			Heap* heap;
			DestructorThread* destructorThread;
			NativeMutex* mutex;

			TraverseContext* lastContext;

			GarbageCollector();
		public:
			static GarbageCollector* getGarbageCollector();

			void gc();

			virtual ~GarbageCollector();
		};

	}
}

#endif
