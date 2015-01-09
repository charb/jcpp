#include "jcpp/lang/reflect/JInvocationHandler.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JClassLoader.h"

namespace jcpp{
    namespace lang{
        namespace reflect{
            class JInvocationHandlerClass : public jcpp::lang::JClass{
            public:
                JInvocationHandlerClass():jcpp::lang::JClass(){
                    canonicalName=new JString("java.lang.reflect.InvocationHandler");
                    name=new JString("java.lang.reflect.InvocationHandler");
                    simpleName=new JString("InvocationHandler");
                    bIsInterface=true;
                }

                virtual jcpp::lang::JClass* getSuperclass(){
                    return JInterface::getClazz();
                }
            };

            static jcpp::lang::JClass* clazz;

            jcpp::lang::JClass* JInvocationHandler::getClazz(){
                if (clazz==null){
                    clazz= new JInvocationHandlerClass();
                }
                return clazz;
            }

            JInvocationHandler::~JInvocationHandler(){
            }
        }
    }
}
