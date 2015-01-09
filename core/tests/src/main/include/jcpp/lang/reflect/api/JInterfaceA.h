#ifndef JCPP_JINTERFACEA_H
#define JCPP_JINTERFACEA_H

#include "jcpp/lang/JInterface.h"

using namespace jcpp::lang;

namespace jcpp{
	namespace lang{
		class JClass;
		class JObject;
	}

	namespace lang{
		namespace reflect{
			namespace api {

			    //@Class(canonicalName="java.InterfaceA", simpleName="InterfaceA");
				class JCPP_EXPORT JInterfaceA : public JInterface{
				public:
					static jcpp::lang::JClass* getClazz();
					virtual ~JInterfaceA();
					int publicIntFieldA ;
				};
			}
		}
	}
}

#endif
