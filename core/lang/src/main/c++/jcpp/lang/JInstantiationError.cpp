#include "jcpp/lang/JInstantiationError.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{
        class JInstantiationErrorClass : public jcpp::lang::JClass{
        protected:
            static JObject* createJInstantiationError(jcpp::util::JList* args){
                return new JInstantiationError();
            }
        
        public:
            JInstantiationErrorClass():jcpp::lang::JClass(){
                canonicalName=new JString("java.lang.InstantiationError");
                name=new JString("java.lang.InstantiationError");
                simpleName=new JString("InstantiationError");
                serialVersionUID=-4885810657349421204LL;
            }

            virtual void initialize(){
                addConstructor(new JConstructor(JInstantiationError::getClazz(),JModifier::PUBLIC,createJInstantiationError));
            }

            virtual jcpp::lang::JClass* getSuperclass(){
                return JIncompatibleClassChangeError::getClazz();
            }
        };

        static jcpp::lang::JClass* clazz;

        jcpp::lang::JClass* JInstantiationError::getClazz(){
            if (clazz==null){
                clazz=new JInstantiationErrorClass();
            }
            return clazz;
        }

        JInstantiationError::JInstantiationError():JIncompatibleClassChangeError(getClazz()){
        }

        JInstantiationError::JInstantiationError(jcpp::lang::JClass* _class):JIncompatibleClassChangeError(_class){
        }

        JInstantiationError::JInstantiationError(JString* message):JIncompatibleClassChangeError(getClazz()){
            this->message = message;
        }

        JInstantiationError::JInstantiationError(JString* message, JThrowable *cause):JIncompatibleClassChangeError(getClazz()){
            this->message = message;
            this->cause = cause;
        }

        JInstantiationError::~JInstantiationError(){
        }
    }
}

