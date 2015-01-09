#include "jcpp/lang/JStringIndexOutOfBoundsException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{
        class JStringIndexOutOfBoundsExceptionClass : public jcpp::lang::JClass{
        protected:
            static JObject* createJStringIndexOutOfBoundsException(jcpp::util::JList* args){
                return new JStringIndexOutOfBoundsException();
            }

        public:
            JStringIndexOutOfBoundsExceptionClass():jcpp::lang::JClass(){
                canonicalName=new JString("java.lang.StringIndexOutOfBoundsException");
                name=new JString("java.lang.StringIndexOutOfBoundsException");
                simpleName=new JString("StringIndexOutOfBoundsException");
                serialVersionUID=-6762910422159637258LL;
            }

            virtual void initialize(){
                addConstructor(new JConstructor(JStringIndexOutOfBoundsException::getClazz(),JModifier::PUBLIC,createJStringIndexOutOfBoundsException));
            }

            virtual jcpp::lang::JClass* getSuperclass(){
                return JIndexOutOfBoundsException::getClazz();
            }
        };

        static jcpp::lang::JClass* clazz;

        jcpp::lang::JClass* JStringIndexOutOfBoundsException::getClazz(){
            if (clazz==null){
                clazz=new JStringIndexOutOfBoundsExceptionClass();
            }
            return clazz;
        }

        JStringIndexOutOfBoundsException::JStringIndexOutOfBoundsException(jcpp::lang::JClass* _class):JIndexOutOfBoundsException(_class){
        }

        JStringIndexOutOfBoundsException::JStringIndexOutOfBoundsException():JIndexOutOfBoundsException(getClazz()){
        }

        JStringIndexOutOfBoundsException::JStringIndexOutOfBoundsException(JString* message):JIndexOutOfBoundsException(getClazz()){
            setMessage(message);
        }

        JStringIndexOutOfBoundsException::~JStringIndexOutOfBoundsException(){
        }
    }
}
