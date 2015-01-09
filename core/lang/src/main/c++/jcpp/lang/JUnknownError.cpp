#include "jcpp/lang/JUnknownError.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{
        class JUnknownErrorClass : public jcpp::lang::JClass{
        protected:
            static JObject* createJUnknownError(jcpp::util::JList* args){
                return new JUnknownError();
            }

        public:
            JUnknownErrorClass():jcpp::lang::JClass(){
                canonicalName=new JString("java.lang.UnknownError");
                name=new JString("java.lang.UnknownError");
                simpleName=new JString("UnknownError");
                serialVersionUID=2524784860676771849LL;
            }

            virtual void initialize(){
                addConstructor(new JConstructor(JUnknownError::getClazz(),JModifier::PUBLIC,createJUnknownError));
            }

            virtual jcpp::lang::JClass* getSuperclass(){
                return JVirtualMachineError::getClazz();
            }
        };

        static jcpp::lang::JClass* clazz;

        jcpp::lang::JClass* JUnknownError::getClazz(){
            if (clazz==null){
                clazz=new JUnknownErrorClass();
            }
            return clazz;
        }

        JUnknownError::JUnknownError():JVirtualMachineError(getClazz()){
        }

        JUnknownError::JUnknownError(jcpp::lang::JClass* _class):JVirtualMachineError(_class){
        }

        JUnknownError::JUnknownError(JString* message):JVirtualMachineError(getClazz()){
            this->message = message;
        }

        JUnknownError::~JUnknownError(){
        }
    }
}

