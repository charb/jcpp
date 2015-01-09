#include "jcpp/gc/info/FieldInfo.h"
#include "jcpp/gc/info/ObjectInfo.h"
#include "jcpp/gc/info/ClassInfo.h"

namespace jcpp {
	namespace gc {
		namespace info {

			FieldInfo::FieldInfo(const char* name, void** pointer) : PointerInfo(pointer), name(name), staticField(false) {
			}

			FieldInfo::FieldInfo(ClassInfo* classInfo, const char* name, void** pointer) : PointerInfo(pointer), name(name), staticField(true) {
				classInfo->addStaticFieldInfo(this);
			}

			NativeString FieldInfo::getName() const {
				return name;
			}

			jbool FieldInfo::isStaticField() const {
				return staticField;
			}

			FieldInfo::~FieldInfo() {
			}

		}
	}
}
