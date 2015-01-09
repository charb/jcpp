#ifndef JCPP_JINTERFACEB_H
#define JCPP_JINTERFACEB_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
using namespace jcpp::lang;

namespace jcpp{
	namespace lang{
		class JClass;
		class JObject;
	}

	namespace lang{
		namespace reflect{
			namespace api {
			    //@Class(canonicalName="java.InterfaceB", simpleName="InterfaceB");
				class JCPP_EXPORT JInterfaceB : public JInterface{
				public:
					static jcpp::lang::JClass* getClazz();
					virtual ~JInterfaceB();
					int publicField;
					int publicIntFieldB;
				};
			}}}
}

#endif
