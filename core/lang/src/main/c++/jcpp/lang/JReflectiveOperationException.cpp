#include "jcpp/lang/JReflectiveOperationException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{
        class JReflectiveOperationExceptionClass : public jcpp::lang::JClass{
        protected:
            static JObject* createJReflectiveOperationException(jcpp::util::JList* args){
                return new JReflectiveOperationException();
            }
            
        public:
            JReflectiveOperationExceptionClass():jcpp::lang::JClass(){
                canonicalName=new JString("java.lang.ReflectiveOperationException");
                name=new JString("java.lang.ReflectiveOperationException");
                simpleName=new JString("ReflectiveOperationException");
                serialVersionUID=123456789L;
            }

            virtual void initialize(){
                addConstructor(new JConstructor(JReflectiveOperationException::getClazz(),JModifier::PUBLIC,createJReflectiveOperationException));
            }

            virtual jcpp::lang::JClass* getSuperclass(){
                return JException::getClazz();
            }
        };

        static jcpp::lang::JClass* clazz;

        jcpp::lang::JClass* JReflectiveOperationException::getClazz(){
            if (clazz==null){
                clazz=new JReflectiveOperationExceptionClass();
            }
            return clazz;
        }

        JReflectiveOperationException::JReflectiveOperationException():JException(getClazz()){
        }

        JReflectiveOperationException::JReflectiveOperationException(jcpp::lang::JClass* _class):JException(_class){
        }

        JReflectiveOperationException::JReflectiveOperationException(JString* message):JException(getClazz()){
            setMessage(message);
        }

        JReflectiveOperationException::JReflectiveOperationException(JString* message,JThrowable* cause):JException(getClazz()){
            setMessage(message);
            setCause(cause);
        }

        JReflectiveOperationException::~JReflectiveOperationException(){
        }
    }
}

