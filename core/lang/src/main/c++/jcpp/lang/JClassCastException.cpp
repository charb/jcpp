#include "jcpp/lang/JClassCastException.h"
#include "jcpp/lang/reflect/JField.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{
        class JClassCastExceptionClass : public jcpp::lang::JClass{
        protected:
            static JObject* createJClassCastException(jcpp::util::JList* args){
                return new JClassCastException();
            }

        public:
            JClassCastExceptionClass():jcpp::lang::JClass(){
                canonicalName=new JString("java.lang.ClassCastException");
                name=new JString("java.lang.ClassCastException");
                simpleName=new JString("ClassCastException");
                serialVersionUID=-9223365651070458532ULL;
            }

            virtual void initialize(){
                JConstructor* cons=addConstructor(new JConstructor(JClassCastException::getClazz(),JModifier::PUBLIC,createJClassCastException));
            }

            virtual jcpp::lang::JClass* getSuperclass(){
                return JRuntimeException::getClazz();
            }
        };

        static jcpp::lang::JClass* clazz;

        jcpp::lang::JClass* JClassCastException::getClazz(){
            if (clazz==null){
                clazz=new JClassCastExceptionClass();
            }
            return clazz;
        }

        JClassCastException::JClassCastException():JRuntimeException(getClazz()){
        }

        JClassCastException::JClassCastException(JString* message):JRuntimeException(getClazz()){
            setMessage(message);
        }

        JClassCastException::~JClassCastException(){
        }
    }
}
