#include "jcpp/lang/reflect/JAnnotatedElement.h"
#include "jcpp/lang/JClass.h"

namespace jcpp{
    namespace lang{
        namespace reflect{
            class JAnnotatedElementClass : public jcpp::lang::JClass{
                public:
                    JAnnotatedElementClass():jcpp::lang::JClass(){
                        canonicalName=new JString("java.lang.reflect.AnnotatedElement");
                        name=new JString("java.lang.reflect.AnnotatedElement");
                        simpleName=new JString("AnnotatedElement");
                        bIsInterface=true;
                    }

                    virtual jcpp::lang::JClass* getSuperclass(){
                        return JInterface::getClazz();
                    }
            };

            static jcpp::lang::JClass* clazz;

            jcpp::lang::JClass* JAnnotatedElement::getClazz(){
                if (clazz==null){
                    clazz=new JAnnotatedElementClass();
                }
                return clazz;
            }

            JAnnotatedElement::~JAnnotatedElement(){
            }
        }
    }
}

