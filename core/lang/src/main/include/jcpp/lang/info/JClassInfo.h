#ifndef JCPP_LANG_INFO_JCLASSINFO_H_
#define JCPP_LANG_INFO_JCLASSINFO_H_
#include "jcpp/lang/JObject.h"
#include "jcpp/util/JList.h"
#include "jcpp/lang/info/JFieldInfo.h"


using namespace jcpp::util;

namespace jcpp{
	namespace lang{
		namespace info{
			// @Class(canonicalName="java.lang.info.ClassInfo", simpleName="ClassInfo");
			class JCPP_EXPORT JClassInfo: public JObject {
			private:
				JString* namespaceName;
				JString* className;
				JList* staticFieldInfos;

			public:
				JClassInfo(JString* _namespaceName,JString* _className,jint statiFieldCount);
				void addStaticFieldInfo( JFieldInfo* staticFieldInfo);

				JList* getStaticFieldInfos();
				JString* getClassName();

				JString* getNamespaceName();

				static jcpp::lang::JClass* getClazz();


				virtual ~JClassInfo();

				friend class JFieldInfo;
			};
		}
	}
}



#endif
