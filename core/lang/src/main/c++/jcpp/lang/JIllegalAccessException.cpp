#include "jcpp/lang/JIllegalAccessException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{
        class JIllegalAccessExceptionClass : public jcpp::lang::JClass{
        protected:
            static JObject* createJIllegalAccessException(jcpp::util::JList* args){
                return new JIllegalAccessException();
            }

        public:
            JIllegalAccessExceptionClass():jcpp::lang::JClass(){
                canonicalName=new JString("java.lang.IllegalAccessException");
                name=new JString("java.lang.IllegalAccessException");
                simpleName=new JString("IllegalAccessException");
                serialVersionUID=6616958222490762034LL;
            }

            virtual void initialize(){
                addConstructor(new JConstructor(JIllegalAccessException::getClazz(),JModifier::PUBLIC,createJIllegalAccessException));
            }

            virtual jcpp::lang::JClass* getSuperclass(){
                return JReflectiveOperationException::getClazz();
            }
        };

        static jcpp::lang::JClass* clazz;

        jcpp::lang::JClass* JIllegalAccessException::getClazz(){
            if (clazz==null){
                clazz=new JIllegalAccessExceptionClass();
            }
            return clazz;
        }

        JIllegalAccessException::JIllegalAccessException():JReflectiveOperationException(getClazz()){
        }

        JIllegalAccessException::JIllegalAccessException(JString* message):JReflectiveOperationException(getClazz()){
            setMessage(message);
        }

        JIllegalAccessException::~JIllegalAccessException(){
        }
    }
}

