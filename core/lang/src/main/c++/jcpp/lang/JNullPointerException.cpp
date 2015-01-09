#include "jcpp/lang/JNullPointerException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{
        class JNullPointerExceptionClass : public jcpp::lang::JClass{
        protected:
            static JObject* createJNullPointerException(jcpp::util::JList* args){
                return new JNullPointerException();
            }

        public:
            JNullPointerExceptionClass():jcpp::lang::JClass(){
                canonicalName=new JString("java.lang.NullPointerException");
                name=new JString("java.lang.NullPointerException");
                simpleName=new JString("NullPointerException");
                serialVersionUID=5162710183389028792ULL;
            }

            virtual void initialize(){
                addConstructor(new JConstructor(JNullPointerException::getClazz(),JModifier::PUBLIC,createJNullPointerException));
            }

            virtual jcpp::lang::JClass* getSuperclass(){
                return JRuntimeException::getClazz();
            }
        };

        static jcpp::lang::JClass* clazz;

        jcpp::lang::JClass* JNullPointerException::getClazz(){
            if (clazz==null){
                clazz=new JNullPointerExceptionClass();
            }
            return clazz;
        }

        JNullPointerException::JNullPointerException():JRuntimeException(getClazz()){
        }

        JNullPointerException::JNullPointerException(JString* message):JRuntimeException(getClazz()){
            setMessage(message);
        }

        JNullPointerException::~JNullPointerException(){
        }
    }
}
