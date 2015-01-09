#include "jcpp/lang/JSecurityException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{
        class JSecurityExceptionClass : public jcpp::lang::JClass{
        protected:
            static JObject* createJSecurityException(jcpp::util::JList* args){
                return new JSecurityException();
            }

        public:
            JSecurityExceptionClass():jcpp::lang::JClass(){
                canonicalName=new JString("java.lang.SecurityException");
                name=new JString("java.lang.SecurityException");
                simpleName=new JString("SecurityException");
                serialVersionUID=6878364983674394167LL;
            }

            virtual void initialize(){
                addConstructor(new JConstructor(JSecurityException::getClazz(),JModifier::PUBLIC,createJSecurityException));
            }

            virtual jcpp::lang::JClass* getSuperclass(){
                return JRuntimeException::getClazz();
            }
        };

        static jcpp::lang::JClass* clazz;

        jcpp::lang::JClass* JSecurityException::getClazz(){
            if (clazz==null){
                clazz=new JSecurityExceptionClass();
            }
            return clazz;
        }

        JSecurityException::JSecurityException():JRuntimeException(getClazz()){
        }

        JSecurityException::JSecurityException(jcpp::lang::JClass* _class):JRuntimeException(_class){
        }

        JSecurityException::JSecurityException(JString* message):JRuntimeException(getClazz()){
            setMessage(message);
        }

        JSecurityException::JSecurityException(JString* message,JThrowable* cause):JRuntimeException(getClazz()){
            setMessage(message);
            setCause(cause);
        }

        JSecurityException::~JSecurityException(){
        }
    }
}

