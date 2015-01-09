#include "jcpp/lang/reflect/JMember.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JClassLoader.h"

namespace jcpp{
    namespace lang{
        namespace reflect{

            class JMemberClass : public jcpp::lang::JClass{
            public:
                JMemberClass():jcpp::lang::JClass(){
                    canonicalName=new JString("java.lang.reflect.Member");
                    name=new JString("java.lang.reflect.Member");
                    simpleName=new JString("Member");
                    this->bIsInterface=true;
                }

                virtual jcpp::lang::JClass* getSuperclass(){
                    return JInterface::getClazz();
                }
            };

            static jcpp::lang::JClass* clazz;

            jint JMember::PUBLIC = 0;

            jint JMember::DECLARED = 1;

            jcpp::lang::JClass* JMember::getClazz(){
                if (clazz==null){
                    clazz= new JMemberClass();
                }
                return clazz;
            }

            JMember::~JMember(){
            }
        }
    }
}