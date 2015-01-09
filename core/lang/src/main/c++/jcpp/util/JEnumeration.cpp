#include "jcpp/util/JEnumeration.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JInstantiationException.h"

namespace jcpp{
    namespace util{
        class JEnumerationClass : public jcpp::lang::JClass{
            public:
                JEnumerationClass():jcpp::lang::JClass(){
                    this->canonicalName=new JString("java.util.Enumeration");
                    this->name=new JString("java.util.Enumeration");
                    this->simpleName=new JString("Enumeration");
                    this->bIsInterface=true;
                }

                virtual jcpp::lang::JClass* getSuperclass(){
                    return JInterface::getClazz();
                }
        };

        static jcpp::lang::JClass* clazz;

        jcpp::lang::JClass* JEnumeration::getClazz(){
            if (clazz==null){
                clazz=new JEnumerationClass();
            }
            return clazz;
        }

        JEnumeration::~JEnumeration(){
        }
    }
}


