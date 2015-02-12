#include "jcpp/gc/ObjectInfoGroup.h"

namespace jcpp {
	namespace gc {
		namespace info {

			ObjectInfoGroup::ObjectInfoGroup(jlong address) : objectInfos(null), capacity(-1), size(0), address(address) {
				objectInfos = staticObjectInfos;
			}

			jlong ObjectInfoGroup::getAddress() {
				return address;
			}

			void ObjectInfoGroup::addObjectInfo(ObjectInfo* objectInfo) {
				if(size == OBJECT_INFOS_DEFAULT_SIZE) {
					objectInfos = new ObjectInfo*[2 * OBJECT_INFOS_DEFAULT_SIZE];
					capacity = 2 * OBJECT_INFOS_DEFAULT_SIZE;
					for(jint i = 0; i < OBJECT_INFOS_DEFAULT_SIZE; i++) {
						objectInfos[i] = staticObjectInfos[i];
					}
				} else if(size == capacity) {
					ObjectInfo** newObjectInfos = new ObjectInfo*[capacity + OBJECT_INFOS_DEFAULT_SIZE];
					for(jint i = 0; i < size; i++) {
						newObjectInfos[i] = objectInfos[i];
					}
					delete [] objectInfos;
					objectInfos = newObjectInfos;
					capacity += OBJECT_INFOS_DEFAULT_SIZE;
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
				if(capacity > 0) {
					delete [] objectInfos;
				}
			}

		}
	}
}
