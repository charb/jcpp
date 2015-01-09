#ifndef JCPP_JInterfaceD_H
#define JCPP_JInterfaceD_H

#include "jcpp/lang/JInterface.h"
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
				//@Class(canonicalName="java.InterfaceD", simpleName="InterfaceD");
				class JCPP_EXPORT JInterfaceD: public JInterface {
				public:
					static jcpp::lang::JClass* getClazz();
					virtual ~JInterfaceD();
					int publicIntFieldB;
					int publicIntFieldD;
				};
			}
		}
	}
}

#endif
