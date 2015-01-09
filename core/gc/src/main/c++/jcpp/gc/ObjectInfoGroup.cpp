#include "jcpp/gc/ObjectInfoGroup.h"

namespace jcpp {
	namespace gc {
		namespace info {

			ObjectInfoGroup::ObjectInfoGroup(jlong address) : objectInfos(), address(address) {
			}

			jlong ObjectInfoGroup::getAddress() {
				return address;
			}

			void ObjectInfoGroup::addObjectInfo(ObjectInfo* objectInfo) {
				objectInfos.push_back(objectInfo);
			}

			std::vector<ObjectInfo*>* ObjectInfoGroup::getObjectInfos() {
				return &objectInfos;
			}

			ObjectInfoGroup::~ObjectInfoGroup() {
			}

		}
	}
}
