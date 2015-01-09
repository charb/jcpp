#include "jcpp/lang/JRuntimeException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{
        class JRuntimeExceptionClass : public jcpp::lang::JClass{
        protected:
            static JObject* createJRuntimeException(jcpp::util::JList* args){
                return new JRuntimeException();
            }

        public:
            JRuntimeExceptionClass():jcpp::lang::JClass(){
                canonicalName=new JString("java.lang.RuntimeException");
                name=new JString("java.lang.RuntimeException");
                simpleName=new JString("RuntimeException");
                serialVersionUID=-7034897190745766939ULL;
            }

            virtual void initialize(){
                addConstructor(new JConstructor(JRuntimeException::getClazz(),JModifier::PUBLIC,createJRuntimeException));
            }

            virtual jcpp::lang::JClass* getSuperclass(){
                return JException::getClazz();
            }
        };

        static jcpp::lang::JClass* clazz;

        jcpp::lang::JClass* JRuntimeException::getClazz(){
            if (clazz==null){
                clazz=new JRuntimeExceptionClass();
            }
            return clazz;
        }

        JRuntimeException::JRuntimeException():JException(getClazz()){
        }

        JRuntimeException::JRuntimeException(jcpp::lang::JClass* _class):JException(_class){
        }

        JRuntimeException::JRuntimeException(JString* message):JException(getClazz()){
            setMessage(message);
        }

        JRuntimeException::JRuntimeException(JString* message,JThrowable* cause):JException(getClazz()){
            setMessage(message);
            setCause(cause);
        }

        JRuntimeException::~JRuntimeException(){
        }
    }
}

