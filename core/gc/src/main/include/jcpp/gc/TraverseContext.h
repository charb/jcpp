#ifndef JCPP_GC_TRAVERSE_CONTEXT_H
#define JCPP_GC_TRAVERSE_CONTEXT_H

#include "jcpp/native/api/NativeInclude.h"
#include "jcpp/gc/ObjectInfoGroup.h"
#include "jcpp/gc/info/ClassInfo.h"
#include "jcpp/gc/info/MethodCallInfo.h"
#include <set>

using namespace jcpp::gc::info;

namespace jcpp {
	namespace gc {

		class Heap;

		class JCPP_EXPORT TraverseContext {
		private:
			Heap* heap;

			std::set<jlong> all;
			std::set<jlong> done;

		protected:
			jbool isDone(ObjectInfoGroup* oig);

			void addFieldInfos(std::vector<FieldInfo*>* fieldInfos);
			void addPointerInfo(PointerInfo* pointerInfo);
		public:
			TraverseContext(Heap* heap);

			void addObjectInfoGroup(ObjectInfoGroup* oig);

			void addClassInfo(ClassInfo* ci);

			void addMethodCallInfo(MethodCallInfo* mci);

			std::set<jlong>* getTraversedAddresses();

			std::set<jlong>* getUnMarkedAddresses();

			virtual ~TraverseContext();
		};

	}
}

#endif
