#include "jcpp/lang/JLinkageError.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{
        class JLinkageErrorClass : public jcpp::lang::JClass{
        protected:
            static JObject* createJLinkageError(jcpp::util::JList* args){
                return new JLinkageError();
            }

        public:
            JLinkageErrorClass():jcpp::lang::JClass(){
                canonicalName=new JString("java.lang.LinkageError");
                name=new JString("java.lang.LinkageError");
                simpleName=new JString("LinkageError");
                serialVersionUID=3579600108157160122LL;
            }

            virtual void initialize(){
                addConstructor(new JConstructor(JLinkageError::getClazz(),JModifier::PUBLIC,createJLinkageError));
            }

            virtual jcpp::lang::JClass* getSuperclass(){
                return JError::getClazz();
            }
        };

        static jcpp::lang::JClass* clazz;

        jcpp::lang::JClass* JLinkageError::getClazz(){
            if (clazz==null){
                clazz=new JLinkageErrorClass();
            }
            return clazz;
        }

        JLinkageError::JLinkageError():JError(getClazz()){
        }

        JLinkageError::JLinkageError(jcpp::lang::JClass* _class):JError(_class){
        }

        JLinkageError::JLinkageError(JString* message):JError(getClazz()){
            this->message = message;
        }

        JLinkageError::JLinkageError(JString* message, JThrowable *cause):JError(getClazz()){
            this->message = message;
            this->cause = cause;
        }

        JLinkageError::~JLinkageError(){
        }
    }
}

