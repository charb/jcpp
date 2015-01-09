#include "jcpp/lang/JIncompatibleClassChangeError.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{
        class JIncompatibleClassChangeErrorClass : public jcpp::lang::JClass{
        protected:
            static JObject* createJIncompatibleClassChangeError(jcpp::util::JList* args){
                return new JIncompatibleClassChangeError();
            }

        public:
            JIncompatibleClassChangeErrorClass():jcpp::lang::JClass(){
                canonicalName=new JString("java.lang.IncompatibleClassChangeError");
                name=new JString("java.lang.IncompatibleClassChangeError");
                simpleName=new JString("IncompatibleClassChangeError");
                serialVersionUID=-4914975503642802119LL;
            }

            virtual void initialize(){
                addConstructor(new JConstructor(JIncompatibleClassChangeError::getClazz(),JModifier::PUBLIC,createJIncompatibleClassChangeError));
            }

            virtual jcpp::lang::JClass* getSuperclass(){
                return JLinkageError::getClazz();
            }
        };

        static jcpp::lang::JClass* clazz;

        jcpp::lang::JClass* JIncompatibleClassChangeError::getClazz(){
            if (clazz==null){
                clazz=new JIncompatibleClassChangeErrorClass();
            }
            return clazz;
        }

        JIncompatibleClassChangeError::JIncompatibleClassChangeError():JLinkageError(getClazz()){
        }

        JIncompatibleClassChangeError::JIncompatibleClassChangeError(jcpp::lang::JClass* _class):JLinkageError(_class){
        }

        JIncompatibleClassChangeError::JIncompatibleClassChangeError(JString* message):JLinkageError(getClazz()){
            this->message = message;
        }

        JIncompatibleClassChangeError::JIncompatibleClassChangeError(JString* message, JThrowable *cause):JLinkageError(getClazz()){
            this->message = message;
            this->cause = cause;
        }

        JIncompatibleClassChangeError::~JIncompatibleClassChangeError(){
        }
    }
}

