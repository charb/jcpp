#include "jcpp/lang/reflect/JAccessibleObject.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JClassLoader.h"

namespace jcpp{
    namespace lang{
        namespace reflect{

            class JAccessibleObjectClass : public jcpp::lang::JClass{
            public:
                JAccessibleObjectClass():jcpp::lang::JClass(){
                    canonicalName=new JString("java.lang.reflect.AccessibleObject");
                    name=new JString("java.lang.reflect.AccessibleObject");
                    simpleName=new JString("AccessibleObject");
                }

                virtual jcpp::lang::JClass* getSuperclass(){
                    return JObject::getClazz();
                }
            };

            static jcpp::lang::JClass* clazz;

            jcpp::lang::JClass* JAccessibleObject::getClazz(){
                if (clazz==null){
                    clazz= new JAccessibleObjectClass();
                }
                return clazz;
            }

            JAccessibleObject::JAccessibleObject(jcpp::lang::JClass* clazz):JObject(clazz){
            }

            JAccessibleObject::~JAccessibleObject(){
            }
        }
    }
}

