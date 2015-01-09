#include "jcpp/lang/JIllegalAccessError.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{
        class JIllegalAccessErrorClass : public jcpp::lang::JClass{
        protected:
            static JObject* createJIllegalAccessError(jcpp::util::JList* args){
                return new JIllegalAccessError();
            }

        public:
            JIllegalAccessErrorClass():jcpp::lang::JClass(){
                canonicalName=new JString("java.lang.IllegalAccessError");
                name=new JString("java.lang.IllegalAccessError");
                simpleName=new JString("IllegalAccessError");
                serialVersionUID=-8988904074992417891LL;
            }

            virtual void initialize(){
                addConstructor(new JConstructor(JIllegalAccessError::getClazz(),JModifier::PUBLIC,createJIllegalAccessError));
            }

            virtual jcpp::lang::JClass* getSuperclass(){
                return JIncompatibleClassChangeError::getClazz();
            }
        };

        static jcpp::lang::JClass* clazz;

        jcpp::lang::JClass* JIllegalAccessError::getClazz(){
            if (clazz==null){
                clazz=new JIllegalAccessErrorClass();
            }
            return clazz;
        }

        JIllegalAccessError::JIllegalAccessError():JIncompatibleClassChangeError(getClazz()){
        }

        JIllegalAccessError::JIllegalAccessError(jcpp::lang::JClass* _class):JIncompatibleClassChangeError(_class){
        }

        JIllegalAccessError::JIllegalAccessError(JString* message):JIncompatibleClassChangeError(getClazz()){
            this->message = message;
        }

        JIllegalAccessError::JIllegalAccessError(JString* message, JThrowable *cause):JIncompatibleClassChangeError(getClazz()){
            this->message = message;
            this->cause = cause;
        }

        JIllegalAccessError::~JIllegalAccessError(){
        }
    }
}

