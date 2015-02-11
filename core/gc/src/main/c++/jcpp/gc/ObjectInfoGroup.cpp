#include "jcpp/gc/ObjectInfoGroup.h"

namespace jcpp {
	namespace gc {
		namespace info {

			ObjectInfoGroup::ObjectInfoGroup(jlong address) : objectInfos(null), capacity(DEFAULT_CAPACITY), size(0), address(address) {
				objectInfos = new ObjectInfo*[DEFAULT_CAPACITY];
			}

			jlong ObjectInfoGroup::getAddress() {
				return address;
			}

			void ObjectInfoGroup::addObjectInfo(ObjectInfo* objectInfo) {
				if(size == capacity) {
					ObjectInfo** newObjectInfos = new ObjectInfo*[capacity + DEFAULT_CAPACITY];
					for(jint i = 0; i < size; i++) {
						newObjectInfos[i] = objectInfos[i];
					}
					delete [] objectInfos;
					objectInfos = newObjectInfos;
					capacity += DEFAULT_CAPACITY;
				}
				objectInfos[size++] = objectInfo;
			}

			ObjectInfo** ObjectInfoGroup::getObjectInfos() {
				return objectInfos;
			}

			jint ObjectInfoGroup::getSize() {
				return size;
			}

			ObjectInfoGroup::~ObjectInfoGroup() {
				delete [] objectInfos;
			}

		}
	}
}
