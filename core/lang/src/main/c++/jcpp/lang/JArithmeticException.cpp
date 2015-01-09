#include "jcpp/lang/JArithmeticException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{
        class JArithmeticExceptionClass : public jcpp::lang::JClass{
        protected:
            static JObject* createJArithmeticException(jcpp::util::JList* args){
                return new JArithmeticException();
            }
        public:
            JArithmeticExceptionClass():jcpp::lang::JClass(){
                canonicalName=new JString("java.lang.ArithmeticException");
                name=new JString("java.lang.ArithmeticException");
                simpleName=new JString("ArithmeticException");
                serialVersionUID=2256477558314496007LL;
            }

            virtual void initialize(){
                JConstructor* cons=addConstructor(new JConstructor(JArithmeticException::getClazz(),JModifier::PUBLIC,createJArithmeticException));
            }

            virtual jcpp::lang::JClass* getSuperclass(){
                return JRuntimeException::getClazz();
            }
        };

        static jcpp::lang::JClass* clazz;

        jcpp::lang::JClass* JArithmeticException::getClazz(){
            if (clazz==null){
                clazz=new JArithmeticExceptionClass();
            }
            return clazz;
        }

        JArithmeticException::JArithmeticException():JRuntimeException(getClazz()){
        }

        JArithmeticException::JArithmeticException(JString* message):JRuntimeException(getClazz()){
            setMessage(message);
        }

        JArithmeticException::~JArithmeticException(){
        }
    }
}
