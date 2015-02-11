#ifndef JCPP_GC_INFO_FIELDINFO_H
#define JCPP_GC_INFO_FIELDINFO_H

#include "jcpp/gc/info/PointerInfo.h"
#include "jcpp/native/api/NativeString.h"

using namespace jcpp::native::api;

namespace jcpp {
	namespace gc {
		namespace info {

			class ObjectInfo;
			class ClassInfo;

			class JCPP_EXPORT FieldInfo : public PointerInfo {
			private:
				NativeString* name;
				jbool staticField;
			public:
				FieldInfo(NativeString* name, void** pointer);

				FieldInfo(ClassInfo* classInfo, NativeString* name, void** pointer, jint index);

				NativeString* getName() const;

				jbool isStaticField() const;

				virtual ~FieldInfo();
			};

		}
	}
}

#endif
