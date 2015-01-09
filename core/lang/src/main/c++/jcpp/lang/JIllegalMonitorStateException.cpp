#include "jcpp/lang/JIllegalMonitorStateException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{
        class JIllegalMonitorStateExceptionClass : public jcpp::lang::JClass{
        protected:
            static JObject* createJIllegalMonitorStateException(jcpp::util::JList* args){
                return new JIllegalMonitorStateException();
            }

        public:
            JIllegalMonitorStateExceptionClass():jcpp::lang::JClass(){
                canonicalName=new JString("java.lang.IllegalMonitorStateException");
                name=new JString("java.lang.IllegalMonitorStateException");
                simpleName=new JString("IllegalMonitorStateException");
                serialVersionUID=3713306369498869069LL;
            }

            virtual void initialize(){
                addConstructor(new JConstructor(JIllegalMonitorStateException::getClazz(),JModifier::PUBLIC,createJIllegalMonitorStateException));
            }

            virtual jcpp::lang::JClass* getSuperclass(){
                return JRuntimeException::getClazz();
            }
        };

        static jcpp::lang::JClass* clazz;

        jcpp::lang::JClass* JIllegalMonitorStateException::getClazz(){
            if (clazz==null){
                clazz=new JIllegalMonitorStateExceptionClass();
            }
            return clazz;
        }

        JIllegalMonitorStateException::JIllegalMonitorStateException(jcpp::lang::JClass* _class):JRuntimeException(_class){
        }

        JIllegalMonitorStateException::JIllegalMonitorStateException():JRuntimeException(getClazz()){
        }

        JIllegalMonitorStateException::JIllegalMonitorStateException(JString* message):JRuntimeException(getClazz()){
            setMessage(message);
        }

        JIllegalMonitorStateException::~JIllegalMonitorStateException(){
        }
    }
}


