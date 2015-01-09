#include "jcpp/lang/JNoSuchMethodError.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{
        class JNoSuchMethodErrorClass : public jcpp::lang::JClass{
        protected:
            static JObject* createJNoSuchMethodError(jcpp::util::JList* args){
                return new JNoSuchMethodError();
            }

        public:
            JNoSuchMethodErrorClass():jcpp::lang::JClass(){
                canonicalName=new JString("java.lang.NoSuchMethodError");
                name=new JString("java.lang.NoSuchMethodError");
                simpleName=new JString("NoSuchMethodError");
                serialVersionUID=-3765521442372831335LL;
            }

            virtual void initialize(){
                addConstructor(new JConstructor(JNoSuchMethodError::getClazz(),JModifier::PUBLIC,createJNoSuchMethodError));
            }

            virtual jcpp::lang::JClass* getSuperclass(){
                return JIncompatibleClassChangeError::getClazz();
            }
        };

        static jcpp::lang::JClass* clazz;

        jcpp::lang::JClass* JNoSuchMethodError::getClazz(){
            if (clazz==null){
                clazz=new JNoSuchMethodErrorClass();
            }
            return clazz;
        }

        JNoSuchMethodError::JNoSuchMethodError():JIncompatibleClassChangeError(getClazz()){
        }

        JNoSuchMethodError::JNoSuchMethodError(jcpp::lang::JClass* _class):JIncompatibleClassChangeError(_class){
        }

        JNoSuchMethodError::JNoSuchMethodError(JString* message):JIncompatibleClassChangeError(getClazz()){
            this->message = message;
        }

        JNoSuchMethodError::JNoSuchMethodError(JString* message, JThrowable *cause):JIncompatibleClassChangeError(getClazz()){
            this->message = message;
            this->cause = cause;
        }

        JNoSuchMethodError::~JNoSuchMethodError(){
        }
    }
}

