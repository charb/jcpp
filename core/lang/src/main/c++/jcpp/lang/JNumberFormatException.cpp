#include "jcpp/lang/JNumberFormatException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{
        class JNumberFormatExceptionClass : public jcpp::lang::JClass{
        protected:
            static JObject* createJNumberFormatException(jcpp::util::JList* args){
                return new JNumberFormatException();
            }

        public:
            JNumberFormatExceptionClass():jcpp::lang::JClass(){
                canonicalName=new JString("java.lang.NumberFormatException");
                name=new JString("java.lang.NumberFormatException");
                simpleName=new JString("NumberFormatException");
                serialVersionUID=-2848938806368998894LL;
            }

            virtual void initialize(){
                addConstructor(new JConstructor(JNumberFormatException::getClazz(),JModifier::PUBLIC,createJNumberFormatException));
            }

            virtual jcpp::lang::JClass* getSuperclass(){
                return JIllegalArgumentException::getClazz();
            }
        };

        static jcpp::lang::JClass* clazz;

        jcpp::lang::JClass* JNumberFormatException::getClazz(){
            if (clazz==null){
                clazz=new JNumberFormatExceptionClass();
            }
            return clazz;
        }

        JNumberFormatException::JNumberFormatException(jcpp::lang::JClass* _class):JIllegalArgumentException(_class){
        }

        JNumberFormatException::JNumberFormatException():JIllegalArgumentException(getClazz()){
        }

        JNumberFormatException::JNumberFormatException(JString* message):JIllegalArgumentException(getClazz()){
            setMessage(message);
        }

        JNumberFormatException::~JNumberFormatException(){
        }
    }
}

