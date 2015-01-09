#include "jcpp/lang/JRunnable.h"
#include "jcpp/lang/JClassLoader.h"

namespace jcpp{
    namespace lang{
        class JRunnableClass : public jcpp::lang::JClass{
        public:
        	JRunnableClass() : jcpp::lang::JClass() {
                canonicalName=new JString("java.lang.Runnable");
                name=new JString("java.lang.Runnable");
                simpleName=new JString("Runnable");
                bIsInterface=true;
            }

            virtual jcpp::lang::JClass* getSuperclass(){
                return JInterface::getClazz();
            }
        };

        static jcpp::lang::JClass* clazz;

        jcpp::lang::JClass* JRunnable::getClazz(){
            if (clazz==null){
                clazz=new JRunnableClass();
            }
            return clazz;
        }

        JRunnable::~JRunnable(){
        }
    }
}
