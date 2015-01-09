#include "jcpp/lang/JVirtualMachineError.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{
        class JVirtualMachineErrorClass : public jcpp::lang::JClass{
        protected:
            static JObject* createJVirtualMachineError(jcpp::util::JList* args){
                return new JVirtualMachineError();
            }

        public:
            JVirtualMachineErrorClass():jcpp::lang::JClass(){
                canonicalName=new JString("java.lang.VirtualMachineError");
                name=new JString("java.lang.VirtualMachineError");
                simpleName=new JString("VirtualMachineError");
                serialVersionUID=4161983926571568670ULL;
            }

            virtual void initialize(){
                addConstructor(new JConstructor(JVirtualMachineError::getClazz(),JModifier::PUBLIC,createJVirtualMachineError));
            }

            virtual jcpp::lang::JClass* getSuperclass(){
                return JError::getClazz();
            }
        };

        static jcpp::lang::JClass* clazz;

        jcpp::lang::JClass* JVirtualMachineError::getClazz(){
            if (clazz==null){
                clazz=new JVirtualMachineErrorClass();
            }
            return clazz;
        }

        JVirtualMachineError::JVirtualMachineError():JError(getClazz()){
        }

        JVirtualMachineError::JVirtualMachineError(jcpp::lang::JClass* _class):JError(_class){
        }

        JVirtualMachineError::JVirtualMachineError(JString* message):JError(getClazz()){
            this->message = message;
        }

        JVirtualMachineError::JVirtualMachineError(JString* message, JThrowable *cause):JError(getClazz()){
            this->message = message;
            this->cause = cause;
        }

        JVirtualMachineError::~JVirtualMachineError(){
        }
    }
}

