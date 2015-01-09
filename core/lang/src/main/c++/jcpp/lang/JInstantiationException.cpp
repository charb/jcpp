#include "jcpp/lang/JInstantiationException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{
        class JInstantiationExceptionClass : public jcpp::lang::JClass{
        protected:
            static JObject* createJInstantiationException(jcpp::util::JList* args){
                return new JInstantiationException();
            }

        public:
            JInstantiationExceptionClass():jcpp::lang::JClass(){
                canonicalName=new JString("java.lang.InstantiationException");
                name=new JString("java.lang.InstantiationException");
                simpleName=new JString("InstantiationException");
                serialVersionUID=-8441929162975509110ULL;
            }

            virtual void initialize(){
                addConstructor(new JConstructor(JInstantiationException::getClazz(),JModifier::PUBLIC,createJInstantiationException));
            }

            virtual jcpp::lang::JClass* getSuperclass(){
                return JReflectiveOperationException::getClazz();
            }
        };

        static jcpp::lang::JClass* clazz;

        jcpp::lang::JClass* JInstantiationException::getClazz(){
            if (clazz==null){
                clazz=new JInstantiationExceptionClass();
            }
            return clazz;
        }

        JInstantiationException::JInstantiationException():JReflectiveOperationException(getClazz()){
        }

        JInstantiationException::JInstantiationException(JString* message):JReflectiveOperationException(getClazz()){
            setMessage(message);
        }

        JInstantiationException::~JInstantiationException(){
        }
    }
}

