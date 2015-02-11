#include "jcpp/gc/info/ClassInfo.h"
#include "jcpp/gc/Heap.h"

namespace jcpp {
	namespace gc {
		namespace info {

			ClassInfo::ClassInfo(const char* namespaceName, const char* className, jint staticFieldCount) :
					namespaceName(namespaceName), className(className), staticFieldInfos(NULL), staticFieldCount(staticFieldCount) {
				if(staticFieldCount > 0) {
					staticFieldInfos = new FieldInfo*[staticFieldCount];
					for(jint staticFieldIndex = 0; staticFieldIndex < staticFieldCount; staticFieldIndex++) {
						staticFieldInfos[staticFieldIndex] = 0;
					}
				}
				Heap::getHeap()->addClassInfo(this);
			}

			void ClassInfo::addStaticFieldInfo(jint index, FieldInfo* staticFieldInfo) {
				staticFieldInfos[index] = staticFieldInfo;
			}

			NativeString* ClassInfo::getClassName() {
				return &className;
			}

			NativeString* ClassInfo::getNamespaceName()  {
				return &namespaceName;
			}

			jint ClassInfo::getStaticFieldCount() const {
				return staticFieldCount;
			}

			FieldInfo** ClassInfo::getStaticFieldInfos() const{
				return staticFieldInfos;
			}

			ClassInfo::~ClassInfo() {
				if(staticFieldInfos) {
					delete [] staticFieldInfos;
				}
			}

		}
	}
}

