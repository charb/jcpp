#include "jcpp/lang/JNoSuchMethodException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{
        class JNoSuchMethodExceptionClass : public jcpp::lang::JClass{
        protected:
            static JObject* createJNoSuchMethodException(jcpp::util::JList* args){
                return new JNoSuchMethodException();
            }

        public:
            JNoSuchMethodExceptionClass():jcpp::lang::JClass(){
                canonicalName=new JString("java.lang.NoSuchMethodException");
                name=new JString("java.lang.NoSuchMethodException");
                simpleName=new JString("NoSuchMethodException");
                serialVersionUID=5034388446362600923ULL;
            }

            virtual void initialize(){
                addConstructor(new JConstructor(JNoSuchMethodException::getClazz(),JModifier::PUBLIC,createJNoSuchMethodException));
            }

            virtual jcpp::lang::JClass* getSuperclass(){
                return JReflectiveOperationException::getClazz();
            }
        };

        static jcpp::lang::JClass* clazz;

        jcpp::lang::JClass* JNoSuchMethodException::getClazz(){
            if (clazz==null){
                clazz=new JNoSuchMethodExceptionClass();
            }
            return clazz;
        }

        JNoSuchMethodException::JNoSuchMethodException():JReflectiveOperationException(getClazz()){
        }

        JNoSuchMethodException::JNoSuchMethodException(JString* message):JReflectiveOperationException(getClazz()){
            setMessage(message);
        }

        JNoSuchMethodException::~JNoSuchMethodException(){
        }
    }
}

