#include "jcpp/lang/JIterable.h"

namespace jcpp{
    namespace lang{

        class JIterableClass : public jcpp::lang::JClass{
          public:
            JIterableClass():jcpp::lang::JClass(){
                this->canonicalName=new JString("java.lang.Iterable");
                this->name=new JString("java.lang.Iterable");
                this->simpleName=new JString("Iterable");
                this->bIsInterface=true;
            }

            virtual jcpp::lang::JClass* getSuperclass(){
                return JInterface::getClazz();
            }
        };

        static jcpp::lang::JClass* clazz;

        jcpp::lang::JClass* JIterable::getClazz(){
            if (clazz==null){
                clazz=new JIterableClass();
            }
            return clazz;
        }

        JIterable::~JIterable(){
        }
    }
}

