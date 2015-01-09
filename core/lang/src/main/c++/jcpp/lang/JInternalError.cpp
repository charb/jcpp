#include "jcpp/lang/JInternalError.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{
        class JInternalErrorClass : public jcpp::lang::JClass{
        protected:
            static JObject* createJInternalError(jcpp::util::JList* args){
                return new JInternalError();
            }

        public:
            JInternalErrorClass():jcpp::lang::JClass(){
                canonicalName=new JString("java.lang.InternalError");
                name=new JString("java.lang.InternalError");
                simpleName=new JString("InternalError");
                serialVersionUID=-9062593416125562365ULL;
            }

            virtual void initialize(){
                addConstructor(new JConstructor(JInternalError::getClazz(),JModifier::PUBLIC,createJInternalError));
            }

            virtual jcpp::lang::JClass* getSuperclass(){
                return JVirtualMachineError::getClazz();
            }
        };

        static jcpp::lang::JClass* clazz;

        jcpp::lang::JClass* JInternalError::getClazz(){
            if (clazz==null){
                clazz=new JInternalErrorClass();
            }
            return clazz;
        }

        JInternalError::JInternalError():JVirtualMachineError(getClazz()){
        }

        JInternalError::JInternalError(jcpp::lang::JClass* _class):JVirtualMachineError(_class){
        }

        JInternalError::JInternalError(JString* message):JVirtualMachineError(getClazz()){
            setMessage(message);
        }

        JInternalError::JInternalError(JString* message, JThrowable *cause):JVirtualMachineError(getClazz()){
            setMessage(message);
            setCause(cause);
        }

        JInternalError::~JInternalError(){
        }
    }
}

