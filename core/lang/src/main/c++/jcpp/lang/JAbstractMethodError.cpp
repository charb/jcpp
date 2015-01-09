#include "jcpp/lang/JAbstractMethodError.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{
        class JAbstractMethodErrorClass : public jcpp::lang::JClass{
        protected:
            static JObject* createJAbstractMethodError(jcpp::util::JList* args){
                return new JAbstractMethodError();
            }
        public:
            JAbstractMethodErrorClass():jcpp::lang::JClass(){
                canonicalName=new JString("java.lang.AbstractMethodError");
                name=new JString("java.lang.AbstractMethodError");
                simpleName=new JString("AbstractMethodError");
                serialVersionUID=-1654391082989018462LL;
            }

            virtual void initialize(){
                JConstructor* cons=addConstructor(new JConstructor(JAbstractMethodError::getClazz(),JModifier::PUBLIC,createJAbstractMethodError));
            }

            virtual jcpp::lang::JClass* getSuperclass(){
                return JIncompatibleClassChangeError::getClazz();
            }
        };

        static jcpp::lang::JClass* clazz = null;

        jcpp::lang::JClass* JAbstractMethodError::getClazz(){
            if (clazz==null){
                clazz=new JAbstractMethodErrorClass();
            }
            return clazz;
        }

        JAbstractMethodError::JAbstractMethodError():JIncompatibleClassChangeError(getClazz()){
        }

        JAbstractMethodError::JAbstractMethodError(jcpp::lang::JClass* _class):JIncompatibleClassChangeError(_class){
        }

        JAbstractMethodError::JAbstractMethodError(JString* message):JIncompatibleClassChangeError(getClazz()){
            this->message = message;
        }

        JAbstractMethodError::JAbstractMethodError(JString* message, JThrowable *cause):JIncompatibleClassChangeError(getClazz()){
            this->message = message;
            this->cause = cause;
        }

        JAbstractMethodError::~JAbstractMethodError(){
        }
    }
}

