#include "jcpp/lang/JNegativeArraySizeException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{
        class JNegativeArraySizeExceptionClass : public jcpp::lang::JClass{
        protected:
            static JObject* createJNegativeArraySizeException(jcpp::util::JList* args){
                return new JNegativeArraySizeException();
            }

        public:
            JNegativeArraySizeExceptionClass():jcpp::lang::JClass(){
                canonicalName=new JString("java.lang.NegativeArraySizeException");
                name=new JString("java.lang.NegativeArraySizeException");
                simpleName=new JString("NegativeArraySizeException");
                serialVersionUID=-8960118058596991861LL;
            }

            virtual void initialize(){
                addConstructor(new JConstructor(JNegativeArraySizeException::getClazz(),JModifier::PUBLIC,createJNegativeArraySizeException));
            }

            virtual jcpp::lang::JClass* getSuperclass(){
                return JRuntimeException::getClazz();
            }
        };

        static jcpp::lang::JClass* clazz;

        jcpp::lang::JClass* JNegativeArraySizeException::getClazz(){
            if (clazz==null){
                clazz=new JNegativeArraySizeExceptionClass();
            }
            return clazz;
        }

        JNegativeArraySizeException::JNegativeArraySizeException(jcpp::lang::JClass* _class):JRuntimeException(_class){
        }

        JNegativeArraySizeException::JNegativeArraySizeException():JRuntimeException(getClazz()){
        }

        JNegativeArraySizeException::JNegativeArraySizeException(JString* message):JRuntimeException(getClazz()){
            setMessage(message);
        }

        JNegativeArraySizeException::JNegativeArraySizeException(JString* message,JThrowable* cause):JRuntimeException(getClazz()){
            setMessage(message);
            setCause(cause);
        }

        JNegativeArraySizeException::~JNegativeArraySizeException(){
        }
    }
}

