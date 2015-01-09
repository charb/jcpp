#include "jcpp/lang/JAssertionError.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{
        class JAssertionErrorClass : public jcpp::lang::JClass{
        protected:
            static JObject* createJAssertionError(jcpp::util::JList* args){
                return new JAssertionError();
            }
        public:
            JAssertionErrorClass():jcpp::lang::JClass(){
                canonicalName=new JString("java.lang.AssertionError");
                name=new JString("java.lang.AssertionError");
                simpleName=new JString("AssertionError");
                serialVersionUID=-5013299493970297370LL;
            }

            virtual void initialize(){
                JConstructor* cons=addConstructor(new JConstructor(JAssertionError::getClazz(),JModifier::PUBLIC,createJAssertionError));
            }

            virtual jcpp::lang::JClass* getSuperclass(){
                return JError::getClazz();
            }
        };

        static jcpp::lang::JClass* clazz;

        jcpp::lang::JClass* JAssertionError::getClazz(){
            if (clazz==null){
                clazz=new JAssertionErrorClass();
            }
            return clazz;
        }

        JAssertionError::JAssertionError():JError(getClazz()){
        }

        JAssertionError::JAssertionError(jcpp::lang::JClass* _class):JError(_class){
        }

        JAssertionError::JAssertionError(JString* message):JError(getClazz()){
            this->message = message;
        }

        JAssertionError::JAssertionError(JString* message, JThrowable *cause):JError(getClazz()){
            this->message = message;
            this->cause = cause;
        }

        JAssertionError::~JAssertionError(){
        }
    }
}

