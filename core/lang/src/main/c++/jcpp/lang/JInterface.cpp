#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"

namespace jcpp{
    namespace lang{
        class JInterfaceClass : public jcpp::lang::JClass{
            public:
                JInterfaceClass():jcpp::lang::JClass(){
                    canonicalName=new JString("java.lang.Interface");
                    name=new JString("java.lang.Interface");//bof...
                    simpleName=new JString("Interface");
                    bIsInterface=true;
                }

                virtual jcpp::lang::JClass* getSuperclass(){
                    return null;
                }
        };

        static jcpp::lang::JClass* clazz;

        jcpp::lang::JClass* JInterface::getClazz(){
            if (clazz==null){
                clazz=new JInterfaceClass();
            }
            return clazz;
        }

        JInterface::~JInterface(){
        }
    }
}

