#include "jcpp/lang/annotation/JAnnotation.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace lang{
        namespace annotation{
            class JAnnotationClass : public jcpp::lang::JClass{
                public:
                    JAnnotationClass():jcpp::lang::JClass(){
                        canonicalName=new JString("java.lang.annotation.Annotation");
                        name=new JString("java.lang.annotation.Annotation");
                        simpleName=new JString("Annotation");
                        bIsAnnotation=true;
                    }

                    virtual jcpp::lang::JClass* getSuperclass(){
                        return null;
                    }
            };

            static jcpp::lang::JClass* clazz;

            jcpp::lang::JClass* JAnnotation::getClazz(){
                if (clazz==null){
                    clazz=new JAnnotationClass();
                }
                return clazz;
            }

            jcpp::lang::JClass* JAnnotation::annotationType(){
                JObject* obj=dynamic_cast<JObject*>(this);
                return obj->getClass();
            }

            JAnnotation::~JAnnotation(){
            }
        }
    }
}

