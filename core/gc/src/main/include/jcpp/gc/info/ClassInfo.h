#ifndef JCPP_GC_INFO_CLASSINFO_H
#define JCPP_GC_INFO_CLASSINFO_H

#include "jcpp/gc/info/FieldInfo.h"
#include "jcpp/native/api/NativeString.h"
#include <vector>

using namespace jcpp::native::api;

namespace jcpp {
	namespace gc {
		namespace info {

			class JCPP_EXPORT ClassInfo {

			private:

				NativeString namespaceName;

				NativeString className;

				jint staticFieldCount;
				FieldInfo** staticFieldInfos;

				void addStaticFieldInfo(jint index, FieldInfo* staticFieldInfo);
			public:
				ClassInfo(const char* namespaceName, const char* className, jint staticFieldCount);

				jint getStaticFieldCount() const;

				FieldInfo** getStaticFieldInfos() const;

				NativeString* getClassName();

				NativeString* getNamespaceName();

				virtual ~ClassInfo();

				friend class FieldInfo;
			};

		}
	}
}

#endif
