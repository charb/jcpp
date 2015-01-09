#include "jcpp/lang/JVerifyError.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{
        class JVerifyErrorClass : public jcpp::lang::JClass{
        protected:
            static JObject* createJVerifyError(jcpp::util::JList* args){
                return new JVerifyError();
            }

        public:
            JVerifyErrorClass():jcpp::lang::JClass(){
                canonicalName=new JString("java.lang.VerifyError");
                name=new JString("java.lang.VerifyError");
                simpleName=new JString("VerifyError");
                serialVersionUID=7001962396098498785LL;
            }

            virtual void initialize(){
                addConstructor(new JConstructor(JVerifyError::getClazz(),JModifier::PUBLIC,createJVerifyError));
            }

            virtual jcpp::lang::JClass* getSuperclass(){
                return JLinkageError::getClazz();
            }
        };

        static jcpp::lang::JClass* clazz;

        jcpp::lang::JClass* JVerifyError::getClazz(){
            if (clazz==null){
                clazz=new JVerifyErrorClass();
            }
            return clazz;
        }

        JVerifyError::JVerifyError():JLinkageError(getClazz()){
        }

        JVerifyError::JVerifyError(jcpp::lang::JClass* _class):JLinkageError(_class){
        }

        JVerifyError::JVerifyError(JString* message):JLinkageError(getClazz()){
            this->message = message;
        }

        JVerifyError::~JVerifyError(){
        }
    }
}

