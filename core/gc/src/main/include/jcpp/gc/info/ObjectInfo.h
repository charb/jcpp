#ifndef JCPP_GC_INFO_OBJECTINFO_H
#define JCPP_GC_INFO_OBJECTINFO_H

#include "jcpp/native/api/NativeInclude.h"
#include "jcpp/gc/info/FieldInfo.h"
#include "jcpp/gc/info/ClassInfo.h"

namespace jcpp {
	namespace gc {
		namespace info {

			class JCPP_EXPORT ObjectInfo {
			private:
				void* objectPointer;

				ClassInfo* classInfo;

				jint fieldCount;
				FieldInfo** fieldInfos;

			public:

				ObjectInfo(ClassInfo* classInfo, void* objectPointer, jint fieldCount, FieldInfo** fieldInfos);

				void* getObjectPointer() const;

				jlong getAddress() const;

				ClassInfo* getClassInfo() const;

				jint getFieldCount() const;
				FieldInfo** getFieldInfos() const;

				void addFieldInfo(jint index, FieldInfo* fieldInfo);

				virtual ~ObjectInfo();

				friend class FieldInfo;
			};

		}
	}
}

#endif
