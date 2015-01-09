#include "jcpp/lang/JNoSuchFieldError.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{
        class JNoSuchFieldErrorClass : public jcpp::lang::JClass{
        protected:
            static JObject* createJNoSuchFieldError(jcpp::util::JList* args){
                return new JNoSuchFieldError();
            }

        public:
            JNoSuchFieldErrorClass():jcpp::lang::JClass(){
                canonicalName=new JString("java.lang.NoSuchFieldError");
                name=new JString("java.lang.NoSuchFieldError");
                simpleName=new JString("NoSuchFieldError");
                serialVersionUID=-3456430195886129035LL;
            }

            virtual void initialize(){
                addConstructor(new JConstructor(JNoSuchFieldError::getClazz(),JModifier::PUBLIC,createJNoSuchFieldError));
            }

            virtual jcpp::lang::JClass* getSuperclass(){
                return JIncompatibleClassChangeError::getClazz();
            }
        };

        static jcpp::lang::JClass* clazz;

        jcpp::lang::JClass* JNoSuchFieldError::getClazz(){
            if (clazz==null){
                clazz=new JNoSuchFieldErrorClass();
            }
            return clazz;
        }

        JNoSuchFieldError::JNoSuchFieldError():JIncompatibleClassChangeError(getClazz()){
        }

        JNoSuchFieldError::JNoSuchFieldError(jcpp::lang::JClass* _class):JIncompatibleClassChangeError(_class){
        }

        JNoSuchFieldError::JNoSuchFieldError(JString* message):JIncompatibleClassChangeError(getClazz()){
            this->message = message;
        }

        JNoSuchFieldError::JNoSuchFieldError(JString* message, JThrowable *cause):JIncompatibleClassChangeError(getClazz()){
            this->message = message;
            this->cause = cause;
        }

        JNoSuchFieldError::~JNoSuchFieldError(){
        }
    }
}

