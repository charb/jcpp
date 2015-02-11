#ifndef JCPP_GC_INFO_OBJECTINFOGROUP_H
#define JCPP_GC_INFO_OBJECTINFOGROUP_H

#include "jcpp/gc/info/ObjectInfo.h"

namespace jcpp {
	namespace gc {
		namespace info {

			class JCPP_EXPORT ObjectInfoGroup {
			private:
				static const jint DEFAULT_CAPACITY = 7;

				jlong address;

				ObjectInfo** objectInfos;
				jint capacity;
				jint size;

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
