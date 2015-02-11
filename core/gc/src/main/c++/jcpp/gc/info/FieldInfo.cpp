#include "jcpp/gc/info/FieldInfo.h"
#include "jcpp/gc/info/ObjectInfo.h"
#include "jcpp/gc/info/ClassInfo.h"

namespace jcpp {
	namespace gc {
		namespace info {

			FieldInfo::FieldInfo(NativeString* name, void** pointer) : PointerInfo(pointer), name(name), staticField(false) {
			}

			FieldInfo::FieldInfo(ClassInfo* classInfo, NativeString* name, void** pointer, jint index) : PointerInfo(pointer), name(name), staticField(true) {
				classInfo->addStaticFieldInfo(index, this);
			}

			NativeString* FieldInfo::getName() const {
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
