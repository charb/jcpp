#include "jcpp/lang/JUnsupportedOperationException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{
        class JUnsupportedOperationExceptionClass : public jcpp::lang::JClass{
        protected:
            static JObject* createJUnsupportedOperationException(jcpp::util::JList* args){
                return new JUnsupportedOperationException();
            }

        public:
            JUnsupportedOperationExceptionClass():jcpp::lang::JClass(){
                canonicalName=new JString("java.lang.UnsupportedOperationException");
                name=new JString("java.lang.UnsupportedOperationException");
                simpleName=new JString("UnsupportedOperationException");
                serialVersionUID=-1242599979055084673ULL;
            }

            virtual void initialize(){
                addConstructor(new JConstructor(JUnsupportedOperationException::getClazz(),JModifier::PUBLIC,createJUnsupportedOperationException));
            }

            virtual jcpp::lang::JClass* getSuperclass(){
                return JRuntimeException::getClazz();
            }
        };

        static jcpp::lang::JClass* clazz;

        jcpp::lang::JClass* JUnsupportedOperationException::getClazz(){
            if (clazz==null){
                clazz=new JUnsupportedOperationExceptionClass();
            }
            return clazz;
        }

        JUnsupportedOperationException::JUnsupportedOperationException(jcpp::lang::JClass* _class):JRuntimeException(_class){
        }

        JUnsupportedOperationException::JUnsupportedOperationException():JRuntimeException(getClazz()){
        }

        JUnsupportedOperationException::JUnsupportedOperationException(JString* message):JRuntimeException(getClazz()){
            this->message=message;
        }

        JUnsupportedOperationException::~JUnsupportedOperationException(){
        }
    }
}



