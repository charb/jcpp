#include "jcpp/lang/JArrayIndexOutOfBoundsException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{
        class JArrayIndexOutOfBoundsExceptionClass : public jcpp::lang::JClass{
        protected:
            static JObject* createJArrayIndexOutOfBoundsException(jcpp::util::JList* args){
                return new JArrayIndexOutOfBoundsException();
            }
        public:
            JArrayIndexOutOfBoundsExceptionClass():jcpp::lang::JClass(){
                canonicalName=new JString("java.lang.ArrayIndexOutOfBoundsException");
                name=new JString("java.lang.ArrayIndexOutOfBoundsException");
                simpleName=new JString("ArrayIndexOutOfBoundsException");
            }

            virtual void initialize(){
                JConstructor* cons=addConstructor(new JConstructor(JArrayIndexOutOfBoundsException::getClazz(),JModifier::PUBLIC,createJArrayIndexOutOfBoundsException));
            }

            virtual jcpp::lang::JClass* getSuperclass(){
                return JIndexOutOfBoundsException::getClazz();
            }
        };

        static jcpp::lang::JClass* clazz;

        jcpp::lang::JClass* JArrayIndexOutOfBoundsException::getClazz(){
            if (clazz==null){
                clazz=new JArrayIndexOutOfBoundsExceptionClass();
            }
            return clazz;
        }

        JArrayIndexOutOfBoundsException::JArrayIndexOutOfBoundsException():JIndexOutOfBoundsException(getClazz()){
        }

        JArrayIndexOutOfBoundsException::JArrayIndexOutOfBoundsException(JString* message):JIndexOutOfBoundsException(getClazz()){
            setMessage(message);
        }

        JArrayIndexOutOfBoundsException::~JArrayIndexOutOfBoundsException(){
        }
    }
}
