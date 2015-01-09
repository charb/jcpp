#ifndef JCPP_JCLASSB_H
#define JCPP_JCLASSB_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/reflect/api/JInterfaceA.h"
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

			    //@Class(canonicalName="java.ClassB", simpleName="ClassB");
					class JCPP_EXPORT JClassB : public JObject, public JInterfaceA{
					public:
						static jcpp::lang::JClass* getClazz();
						virtual ~JClassB();
						int publicFieldB;
						int publicField;
						int protectedFieldB;
						int privateField;
					};
			}}}
}

#endif
