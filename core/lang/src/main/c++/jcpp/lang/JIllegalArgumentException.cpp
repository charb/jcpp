#include "jcpp/lang/JIllegalArgumentException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{
        class JIllegalArgumentExceptionClass : public jcpp::lang::JClass{
        protected:
            static JObject* createJIllegalArgumentException(jcpp::util::JList* args){
                return new JIllegalArgumentException();
            }

        public:
            JIllegalArgumentExceptionClass():jcpp::lang::JClass(){
                canonicalName=new JString("java.lang.IllegalArgumentException");
                name=new JString("java.lang.IllegalArgumentException");
                simpleName=new JString("IllegalArgumentException");
                serialVersionUID=-5365630128856068164ULL;
            }

            virtual void initialize(){
                addConstructor(new JConstructor(JIllegalArgumentException::getClazz(),JModifier::PUBLIC,createJIllegalArgumentException));
            }

            virtual jcpp::lang::JClass* getSuperclass(){
                return JRuntimeException::getClazz();
            }
        };

        static jcpp::lang::JClass* clazz;

        jcpp::lang::JClass* JIllegalArgumentException::getClazz(){
            if (clazz==null){
                clazz=new JIllegalArgumentExceptionClass();
            }
            return clazz;
        }

        JIllegalArgumentException::JIllegalArgumentException(jcpp::lang::JClass* _class):JRuntimeException(_class){
        }

        JIllegalArgumentException::JIllegalArgumentException():JRuntimeException(getClazz()){
        }

        JIllegalArgumentException::JIllegalArgumentException(JString* message):JRuntimeException(getClazz()){
            setMessage(message);
        }

        JIllegalArgumentException::JIllegalArgumentException(JString* message,JThrowable* cause):JRuntimeException(getClazz()){
            setMessage(message);
            setCause(cause);
        }

        JIllegalArgumentException::~JIllegalArgumentException(){
        }
    }
}

