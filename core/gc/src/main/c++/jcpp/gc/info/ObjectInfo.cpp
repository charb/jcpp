#include "jcpp/gc/info/ObjectInfo.h"
#include "jcpp/gc/Heap.h"

namespace jcpp {
	namespace gc {
		namespace info {

			ObjectInfo::ObjectInfo(ClassInfo* classInfo, void* objectPointer) :
					classInfo(classInfo), objectPointer(objectPointer), fieldInfos() {
				Heap::getHeap()->addCreatedObject(this);
			}

			void ObjectInfo::addFieldInfo(FieldInfo* fieldInfo) {
				fieldInfos.push_back(fieldInfo);
			}

			void* ObjectInfo::getObjectPointer() const {
				return objectPointer;
			}

			jlong ObjectInfo::getAddress() const {
				return (jlong) objectPointer;
			}

			ClassInfo* ObjectInfo::getClassInfo() const {
				return classInfo;
			}

			std::vector<FieldInfo*>* ObjectInfo::getFieldInfos() {
				return &fieldInfos;
			}

			ObjectInfo::~ObjectInfo() {
			}

		}
	}
}
