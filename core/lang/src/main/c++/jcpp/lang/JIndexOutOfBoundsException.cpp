#include "jcpp/lang/JIndexOutOfBoundsException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{
        class JIndexOutOfBoundsExceptionClass : public jcpp::lang::JClass{
        protected:
            static JObject* createJIndexOutOfBoundsException(jcpp::util::JList* args){
                return new JIndexOutOfBoundsException();
            }
        
        public:
            JIndexOutOfBoundsExceptionClass():jcpp::lang::JClass(){
                canonicalName=new JString("java.lang.IndexOutOfBoundsException");
                name=new JString("java.lang.IndexOutOfBoundsException");
                simpleName=new JString("IndexOutOfBoundsException");
                serialVersionUID=234122996006267687ULL;
            }

            virtual void initialize(){
                addConstructor(new JConstructor(JIndexOutOfBoundsException::getClazz(),JModifier::PUBLIC,createJIndexOutOfBoundsException));
            }

            virtual jcpp::lang::JClass* getSuperclass(){
                return JRuntimeException::getClazz();
            }
        };

        static jcpp::lang::JClass* clazz;

        jcpp::lang::JClass* JIndexOutOfBoundsException::getClazz(){
            if (clazz==null){
                clazz=new JIndexOutOfBoundsExceptionClass();
            }
            return clazz;
        }

        JIndexOutOfBoundsException::JIndexOutOfBoundsException(jcpp::lang::JClass* _class):JRuntimeException(_class){
        }

        JIndexOutOfBoundsException::JIndexOutOfBoundsException():JRuntimeException(getClazz()){
        }

        JIndexOutOfBoundsException::JIndexOutOfBoundsException(JString* message):JRuntimeException(getClazz()){
            setMessage(message);
        }

        JIndexOutOfBoundsException::~JIndexOutOfBoundsException(){
        }
    }
}
