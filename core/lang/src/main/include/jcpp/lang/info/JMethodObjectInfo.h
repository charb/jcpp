#ifndef JCPP_LANG_INFO_JMETHODOBJECTINFO_H_
#define JCPP_LANG_INFO_JMETHODOBJECTINFO_H_

#include "jcpp/gc/info/PointerInfo.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JPrimitiveLong.h"

using namespace jcpp::gc::info;
using namespace jcpp::lang;

namespace jcpp {
	namespace lang {
		namespace info {
			// @Class(canonicalName="java.lang.info.MethodObjectInfo", simpleName="MethodObjectInfo");
			class JCPP_EXPORT JMethodObjectInfo: public JObject{
			private:
				JPrimitiveLong *address;
			public:
				JMethodObjectInfo(JPrimitiveLong* _address);
				JPrimitiveLong *getAddress();
				static jcpp::lang::JClass* getClazz();
				~JMethodObjectInfo();
			};
		}
	}
}

#endif
