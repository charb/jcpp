#include "jcpp/lang/JAppendable.h"
#include "jcpp/lang/JClass.h"

namespace jcpp{
    namespace lang{
        class JAppendableClass : public jcpp::lang::JClass{
            public:
                JAppendableClass():jcpp::lang::JClass(){
                    this->canonicalName=new JString("java.lang.Appendable");
                    this->name=new JString("java.lang.Appendable");
                    this->simpleName=new JString("Appendable");
                    this->bIsInterface=true;
                }

                virtual jcpp::lang::JClass* getSuperclass(){
                    return JInterface::getClazz();
                }
        };

        static jcpp::lang::JClass* clazz;

        jcpp::lang::JClass* JAppendable::getClazz(){
            if (clazz==null){
                clazz=new JAppendableClass();
            }
            return clazz;
        }

        JAppendable::~JAppendable(){
        }
    }
}
