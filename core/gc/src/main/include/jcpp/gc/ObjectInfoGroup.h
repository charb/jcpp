#ifndef JCPP_GC_INFO_OBJECTINFOGROUP_H
#define JCPP_GC_INFO_OBJECTINFOGROUP_H

#include "jcpp/gc/info/ObjectInfo.h"

namespace jcpp {
	namespace gc {
		namespace info {

			class JCPP_EXPORT ObjectInfoGroup {
			private:
				jlong address;
				std::vector<ObjectInfo*> objectInfos;

			public:
				ObjectInfoGroup(jlong address);

				jlong getAddress();

				std::vector<ObjectInfo*>* getObjectInfos();

				void addObjectInfo(ObjectInfo* objectInfo);

				virtual ~ObjectInfoGroup();
			};

		}
	}
}

#endif
