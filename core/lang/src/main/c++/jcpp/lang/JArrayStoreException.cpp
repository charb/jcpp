#include "jcpp/lang/JArrayStoreException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{
        class JArrayStoreExceptionClass : public jcpp::lang::JClass{
        protected:
            static JObject* createJArrayStoreException(jcpp::util::JList* args){
                return new JArrayStoreException();
            }
        public:
            JArrayStoreExceptionClass():jcpp::lang::JClass(){
                canonicalName=new JString("java.lang.ArrayStoreException");
                name=new JString("java.lang.ArrayStoreException");
                simpleName=new JString("ArrayStoreException");
                serialVersionUID=-4522193890499838241LL;
            }

            virtual void initialize(){
                JConstructor* cons=addConstructor(new JConstructor(JArrayStoreException::getClazz(),JModifier::PUBLIC,createJArrayStoreException));
            }

            virtual jcpp::lang::JClass* getSuperclass(){
                return JRuntimeException::getClazz();
            }
        };

        static jcpp::lang::JClass* clazz;

        jcpp::lang::JClass* JArrayStoreException::getClazz(){
            if (clazz==null){
                clazz=new JArrayStoreExceptionClass();
            }
            return clazz;
        }

        JArrayStoreException::JArrayStoreException():JRuntimeException(getClazz()){
        }

        JArrayStoreException::JArrayStoreException(JString* message):JRuntimeException(getClazz()){
            setMessage(message);
        }

        JArrayStoreException::~JArrayStoreException(){
        }
    }
}
