#ifndef JCPP_GC_HEAP_H
#define JCPP_GC_HEAP_H

#include "jcpp/native/api/NativeInclude.h"
#include "jcpp/native/api/nthread/NativeMutex.h"
#include "jcpp/gc/ObjectInfoGroup.h"
#include "jcpp/gc/info/ClassInfo.h"
#include "jcpp/gc/TraverseContext.h"
#include <map>
#include <vector>
#include <set>

using namespace jcpp::gc::info;
using namespace jcpp::native::api::nthread;

/**
 * TODO
 * Check performance with mutex lock at addCreatedObject (may be create a map per thread)
 *
 */
namespace jcpp {
	namespace gc {

		class JCPP_EXPORT Heap {
		private:
			static Heap* heap;

			std::map<jlong, ObjectInfoGroup*> objectInfoGroupsByAddress;
			std::vector<ClassInfo*> classInfos;
			NativeMutex* objectInfoGroupsMutex;
			NativeMutex* classInfosMutex;

			Heap();
		public:
			static Heap* getHeap();

			void addClassInfo(ClassInfo* ci);

			void addCreatedObject(ObjectInfo* oi);

			void removeObjectsToBeDeleted(std::set<jlong>* addresses);

			void getAllObjectAddresses(std::set<jlong>& addresses);

			ObjectInfoGroup* getObjectInfoGroupFromAddress(jlong address);

			void addRoot(TraverseContext* context);

			virtual ~Heap();
		};

	}
}

#endif
