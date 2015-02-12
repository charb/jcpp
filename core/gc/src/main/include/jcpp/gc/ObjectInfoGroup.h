#ifndef JCPP_GC_INFO_OBJECTINFOGROUP_H
#define JCPP_GC_INFO_OBJECTINFOGROUP_H

#include "jcpp/gc/info/ObjectInfo.h"
#define OBJECT_INFOS_DEFAULT_SIZE 4

namespace jcpp {
	namespace gc {
		namespace info {

			class JCPP_EXPORT ObjectInfoGroup {
			private:
				jlong address;

				ObjectInfo* staticObjectInfos[OBJECT_INFOS_DEFAULT_SIZE];
				ObjectInfo** objectInfos; // used when static object info count > OBJECT_INFOS_DEFAULT_SIZE

				jint size;
				jint capacity;

			public:
				ObjectInfoGroup(jlong address);

				jlong getAddress();

				ObjectInfo** getObjectInfos();

				jint getSize();

				void addObjectInfo(ObjectInfo* objectInfo);

				virtual ~ObjectInfoGroup();
			};

		}
	}
}

#endif
