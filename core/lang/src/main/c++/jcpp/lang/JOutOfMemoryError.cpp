#include "jcpp/lang/JOutOfMemoryError.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{
        class JOutOfMemoryErrorClass : public jcpp::lang::JClass{
        protected:
            static JObject* createJOutOfMemoryError(jcpp::util::JList* args){
                return new JOutOfMemoryError();
            }

        public:
            JOutOfMemoryErrorClass():jcpp::lang::JClass(){
                canonicalName=new JString("java.lang.OutOfMemoryError");
                name=new JString("java.lang.OutOfMemoryError");
                simpleName=new JString("OutOfMemoryError");
                serialVersionUID=8228564086184010517LL;
            }

            virtual void initialize(){
                addConstructor(new JConstructor(JOutOfMemoryError::getClazz(),JModifier::PUBLIC,createJOutOfMemoryError));
            }

            virtual jcpp::lang::JClass* getSuperclass(){
                return JVirtualMachineError::getClazz();
            }
        };

        static jcpp::lang::JClass* clazz;

        jcpp::lang::JClass* JOutOfMemoryError::getClazz(){
            if (clazz==null){
                clazz=new JOutOfMemoryErrorClass();
            }
            return clazz;
        }

        JOutOfMemoryError::JOutOfMemoryError():JVirtualMachineError(getClazz()){
        }

        JOutOfMemoryError::JOutOfMemoryError(jcpp::lang::JClass* _class):JVirtualMachineError(_class){
        }

        JOutOfMemoryError::JOutOfMemoryError(JString* message):JVirtualMachineError(getClazz()){
            this->message = message;
        }

        JOutOfMemoryError::JOutOfMemoryError(JString* message, JThrowable *cause):JVirtualMachineError(getClazz()){
            this->message = message;
            this->cause = cause;
        }

        JOutOfMemoryError::~JOutOfMemoryError(){
        }
    }
}

