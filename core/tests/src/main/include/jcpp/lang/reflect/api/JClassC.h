#ifndef JCPP_JCLASSC_H
#define JCPP_JCLASSC_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/reflect/api/JInterfaceC.h"
#include "jcpp/lang/reflect/api/JInterfaceD.h"
#include "jcpp/lang/reflect/api/JClassB.h"

using namespace jcpp::lang;

namespace jcpp{
	namespace lang{
		class JClass;
		class JObject;
	}

	namespace lang{
		namespace reflect{
			namespace api {

			    //@Class(canonicalName="java.ClassC", simpleName="ClassC");
				class JCPP_EXPORT JClassC : public JClassB, public JInterfaceC, public JInterfaceD{
				public:
					static jcpp::lang::JClass* getClazz();
					virtual ~JClassC();
				};
			}
		}
	}
}

#endif
