#include "jcpp/lang/reflect/JMalformedParametersException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{
        namespace reflect{
            class JMalformedParametersExceptionClass : public jcpp::lang::JClass{
            protected:
                static JObject* createJMalformedParametersException(jcpp::util::JList* args){
                    return new JMalformedParametersException();
                }

            public:
                JMalformedParametersExceptionClass():jcpp::lang::JClass(){
                    canonicalName=new JString("java.lang.reflect.MalformedParametersException");
                    name=new JString("java.lang.reflect.MalformedParametersException");
                    simpleName=new JString("MalformedParametersException");
                    serialVersionUID=20130919L;
                }

                virtual void initialize(){
                    JConstructor* cons=addConstructor(new JConstructor(JMalformedParametersException::getClazz(),JModifier::PUBLIC,createJMalformedParametersException));
                }

                virtual jcpp::lang::JClass* getSuperclass(){
                    return JRuntimeException::getClazz();
                }
            };

            static jcpp::lang::JClass* clazz;

            jcpp::lang::JClass* JMalformedParametersException::getClazz(){
                if (clazz==null){
                    clazz=new JMalformedParametersExceptionClass();
                }
                return clazz;
            }

            JMalformedParametersException::JMalformedParametersException():JRuntimeException(getClazz()){
            }

            JMalformedParametersException::JMalformedParametersException(JString* message):JRuntimeException(getClazz()){
                setMessage(message);
            }

            JMalformedParametersException::~JMalformedParametersException(){
            }
        }
    }
}
