#ifndef JCPP_LANG_REFLECT_JACCESSIBLEOBJECT_H
#define JCPP_LANG_REFLECT_JACCESSIBLEOBJECT_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/reflect/JAnnotatedElement.h"

using namespace std;
using namespace jcpp::lang;

namespace jcpp{
    namespace lang{
        namespace reflect{

        	// @Class(canonicalName="java.lang.reflect.AccessibleObject", simpleName="AccessibleObject");
            class JCPP_EXPORT JAccessibleObject: public JObject, public JAnnotatedElement{

            protected:
                JAccessibleObject(jcpp::lang::JClass* clazz);

            public:
                static jcpp::lang::JClass* getClazz();

                virtual ~JAccessibleObject();
            };
        }
    }
}

#endif
