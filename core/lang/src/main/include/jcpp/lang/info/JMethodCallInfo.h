#ifndef JCPP_LANG_INFO_JMETHODCALLINFO_H_
#define JCPP_LANG_INFO_JMETHODCALLINFO_H_

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JString.h"
#include "jcpp/util/JArrayList.h"
#include "jcpp/lang/info/JObjectInfo.h"
#include "jcpp/lang/info/JMethodObjectInfo.h"

using namespace jcpp::lang;
using namespace jcpp::util;
using namespace jcpp::gc::info;

namespace jcpp {
	namespace lang {
		namespace info {
			// @Class(canonicalName="java.lang.info.MethodCallInfo", simpleName="MethodCallInfo");
			class JCPP_EXPORT JMethodCallInfo: public JObject{
			private:
				JObjectInfo* objectInfo;

				JString* name;
				JList *methodObjects;

			public:
				JMethodCallInfo();
				JMethodCallInfo(JString* name, JObjectInfo* objectInfo);
				JString* getName();
				JObjectInfo* getObjectInfo();
				void addMethodObject(JMethodObjectInfo* methodObjectInfo);
				JList* getMethodObjects();
				static jcpp::lang::JClass* getClazz();

			};
		}
	}
}

#endif
