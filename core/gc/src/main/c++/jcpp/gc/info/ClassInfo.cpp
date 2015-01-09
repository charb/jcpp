#include "jcpp/gc/info/ClassInfo.h"
#include "jcpp/gc/Heap.h"

namespace jcpp {
	namespace gc {
		namespace info {

			ClassInfo::ClassInfo(const char* namespaceName, const char* className) :
					namespaceName(namespaceName), className(className), staticfieldInfos() {
				Heap::getHeap()->addClassInfo(this);
			}

			void ClassInfo::addStaticFieldInfo(FieldInfo* staticFieldInfo) {
				staticfieldInfos.push_back(staticFieldInfo);
			}

			NativeString ClassInfo::getClassName() const {
				return className;
			}

			NativeString ClassInfo::getNamespaceName() const {
				return namespaceName;
			}

			std::vector<FieldInfo*>* ClassInfo::getStaticFieldInfos() {
				return &staticfieldInfos;
			}

			ClassInfo::~ClassInfo() {
			}

		}
	}
}

