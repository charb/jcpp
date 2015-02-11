#include "jcpp/gc/info/ObjectInfo.h"
#include "jcpp/gc/Heap.h"

namespace jcpp {
	namespace gc {
		namespace info {

			ObjectInfo::ObjectInfo(ClassInfo* classInfo, void* objectPointer, jint fieldCount, FieldInfo** fieldInfos) :
					classInfo(classInfo), objectPointer(objectPointer), fieldCount(fieldCount), fieldInfos(fieldInfos) {
				if(fieldCount > 0) {
					for(jint fieldIndex = 0; fieldIndex < fieldCount; fieldIndex++) {
						fieldInfos[fieldIndex] = 0;
					}
				}
				Heap::getHeap()->addCreatedObject(this);
			}

			void ObjectInfo::addFieldInfo(jint index, FieldInfo* fieldInfo) {
				fieldInfos[index] = fieldInfo;
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

			jint ObjectInfo::getFieldCount() const {
				return fieldCount;
			}

			FieldInfo** ObjectInfo::getFieldInfos() const {
				return fieldInfos;
			}

			ObjectInfo::~ObjectInfo() {
			}

		}
	}
}
