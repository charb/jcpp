#include "jcpp/lang/reflect/JAnnotatedType.h"
#include "jcpp/lang/JClass.h"

namespace jcpp{
    namespace lang{
        namespace reflect{
            class JAnnotatedTypeClass : public jcpp::lang::JClass{
                public:
                    JAnnotatedTypeClass():jcpp::lang::JClass(){
                        canonicalName=new JString("java.lang.reflect.AnnotatedType");
                        name=new JString("java.lang.reflect.AnnotatedType");
                        simpleName=new JString("AnnotatedType");
                        bIsInterface=true;
                    }

                    virtual jcpp::lang::JClass* getSuperclass(){
                        return JAnnotatedElement::getClazz();
                    }
            };

            static jcpp::lang::JClass* clazz;

            jcpp::lang::JClass* JAnnotatedType::getClazz(){
                if (clazz==null){
                    clazz=new JAnnotatedTypeClass();
                }
                return clazz;
            }

            JAnnotatedType::~JAnnotatedType(){
            }
        }
    }
}

