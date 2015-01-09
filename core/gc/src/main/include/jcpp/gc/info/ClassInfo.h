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

				std::vector<FieldInfo*> staticfieldInfos;

				void addStaticFieldInfo(FieldInfo* staticFieldInfo);
			public:
				ClassInfo(const char* namespaceName, const char* className);

				std::vector<FieldInfo*>* getStaticFieldInfos();

				NativeString getClassName() const;

				NativeString getNamespaceName() const;

				virtual ~ClassInfo();

				friend class FieldInfo;
			};

		}
	}
}

#endif
