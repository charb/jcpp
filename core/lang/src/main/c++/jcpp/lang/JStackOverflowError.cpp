#include "jcpp/lang/JStackOverflowError.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{
        class JStackOverflowErrorClass : public jcpp::lang::JClass{
        protected:
            static JObject* createJStackOverflowError(jcpp::util::JList* args){
                return new JStackOverflowError();
            }

        public:
            JStackOverflowErrorClass():jcpp::lang::JClass(){
                canonicalName=new JString("java.lang.StackOverflowError");
                name=new JString("java.lang.StackOverflowError");
                simpleName=new JString("StackOverflowError");
                serialVersionUID=8609175038441759607LL;
            }

            virtual void initialize(){
                addConstructor(new JConstructor(JStackOverflowError::getClazz(),JModifier::PUBLIC,createJStackOverflowError));
            }

            virtual jcpp::lang::JClass* getSuperclass(){
                return JVirtualMachineError::getClazz();
            }
        };

        static jcpp::lang::JClass* clazz;

        jcpp::lang::JClass* JStackOverflowError::getClazz(){
            if (clazz==null){
                clazz=new JStackOverflowErrorClass();
            }
            return clazz;
        }

        JStackOverflowError::JStackOverflowError():JVirtualMachineError(getClazz()){
        }

        JStackOverflowError::JStackOverflowError(jcpp::lang::JClass* _class):JVirtualMachineError(_class){
        }

        JStackOverflowError::JStackOverflowError(JString* message):JVirtualMachineError(getClazz()){
            this->message = message;
        }

        JStackOverflowError::~JStackOverflowError(){
        }
    }
}

