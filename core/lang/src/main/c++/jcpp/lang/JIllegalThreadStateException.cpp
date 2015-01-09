#include "jcpp/lang/JIllegalThreadStateException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{
        class JIllegalThreadStateExceptionClass : public jcpp::lang::JClass{
        protected:
            static JObject* createJIllegalThreadStateException(jcpp::util::JList* args){
                return new JIllegalThreadStateException();
            }

        public:
            JIllegalThreadStateExceptionClass():jcpp::lang::JClass(){
                canonicalName=new JString("java.lang.IllegalThreadStateException");
                name=new JString("java.lang.IllegalThreadStateException");
                simpleName=new JString("IllegalThreadStateException");
                serialVersionUID=-7626246362397460174LL;
            }

            virtual void initialize(){
                addConstructor(new JConstructor(JIllegalThreadStateException::getClazz(),JModifier::PUBLIC,createJIllegalThreadStateException));
            }

            virtual jcpp::lang::JClass* getSuperclass(){
                return JIllegalArgumentException::getClazz();
            }

        };

        static jcpp::lang::JClass* clazz;

        jcpp::lang::JClass* JIllegalThreadStateException::getClazz(){
            if (clazz==null){
                clazz=new JIllegalThreadStateExceptionClass();
            }
            return clazz;
        }

        JIllegalThreadStateException::JIllegalThreadStateException(jcpp::lang::JClass* _class):JIllegalArgumentException(_class){
        }

        JIllegalThreadStateException::JIllegalThreadStateException():JIllegalArgumentException(getClazz()){
        }

        JIllegalThreadStateException::JIllegalThreadStateException(JString* message):JIllegalArgumentException(getClazz()){
            setMessage(message);
        }

        JIllegalThreadStateException::JIllegalThreadStateException(JString* message,JThrowable* cause):JIllegalArgumentException(getClazz()){
            setMessage(message);
            setCause(cause);
        }

        JIllegalThreadStateException::~JIllegalThreadStateException(){
        }
    }
}

