#include "jcpp/lang/JIllegalStateException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{
        class JIllegalStateExceptionClass : public jcpp::lang::JClass{
        protected:
            static JObject* createJIllegalStateException(jcpp::util::JList* args){
                return new JIllegalStateException();
            }
        public:
            JIllegalStateExceptionClass():jcpp::lang::JClass(){
                canonicalName=new JString("java.lang.IllegalStateException");
                name=new JString("java.lang.IllegalStateException");
                simpleName=new JString("IllegalStateException");
                serialVersionUID=-1848914673093119416ULL;
            }

            virtual void initialize(){
                addConstructor(new JConstructor(JIllegalStateException::getClazz(),JModifier::PUBLIC,createJIllegalStateException));
            }

            virtual jcpp::lang::JClass* getSuperclass(){
                return JRuntimeException::getClazz();
            }
        };

        static jcpp::lang::JClass* clazz;

        jcpp::lang::JClass* JIllegalStateException::getClazz(){
            if (clazz==null){
                clazz=new JIllegalStateExceptionClass();
            }
            return clazz;
        }

        JIllegalStateException::JIllegalStateException(jcpp::lang::JClass* _class):JRuntimeException(_class){
        }

        JIllegalStateException::JIllegalStateException():JRuntimeException(getClazz()){
        }

        JIllegalStateException::JIllegalStateException(JString* message):JRuntimeException(getClazz()){
            setMessage(message);
        }

        JIllegalStateException::~JIllegalStateException(){
        }
    }
}


