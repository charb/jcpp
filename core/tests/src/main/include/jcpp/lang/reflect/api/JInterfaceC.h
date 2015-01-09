#ifndef JCPP_JINTERFACEC_H
#define JCPP_JINTERFACEC_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/reflect/api/JInterfaceB.h"
#include "jcpp/lang/JClass.h"
using namespace jcpp::lang;

namespace jcpp {
	namespace lang {
		class JClass;
		class JObject;
	}

	namespace lang {
		namespace reflect {
			namespace api {
			    //@Class(canonicalName="java.InterfaceC", simpleName="InterfaceC");
				class JCPP_EXPORT JInterfaceC: public JInterfaceB {
				public:
					static jcpp::lang::JClass* getClazz();
					virtual ~JInterfaceC();
					int publicIntFieldC;
					int publicFieldB;
				};
			}
		}
	}
}

#endif
