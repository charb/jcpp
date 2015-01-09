#include "jcpp/lang/JCharSequence.h"
#include "jcpp/lang/JClass.h"

namespace jcpp{
    namespace lang{

        class JCharSequenceClass : public jcpp::lang::JClass{
            public:
                JCharSequenceClass():jcpp::lang::JClass(){
                    this->canonicalName=new JString("java.lang.CharSequence");
                    this->name=new JString("java.lang.CharSequence");
                    this->simpleName=new JString("CharSequence");
                    this->bIsInterface=true;
                }

                virtual jcpp::lang::JClass* getSuperclass(){
                    return JInterface::getClazz();
                }
        };

        static jcpp::lang::JClass* clazz;

        jcpp::lang::JClass* JCharSequence::getClazz(){
            if (clazz==null){
                clazz=new JCharSequenceClass();
            }
            return clazz;
        }

        JCharSequence::~JCharSequence(){
        }
    }
}
