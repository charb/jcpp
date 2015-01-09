#include "jcpp/lang/reflect/JMalformedParameterizedTypeException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{
        namespace reflect{
            class JMalformedParameterizedTypeExceptionClass : public jcpp::lang::JClass{
            protected:
                static JObject* createJMalformedParameterizedTypeException(jcpp::util::JList* args){
                    return new JMalformedParameterizedTypeException();
                }

            public:
                JMalformedParameterizedTypeExceptionClass():jcpp::lang::JClass(){
                    canonicalName=new JString("java.lang.reflect.MalformedParameterizedTypeException");
                    name=new JString("java.lang.reflect.MalformedParameterizedTypeException");
                    simpleName=new JString("MalformedParameterizedTypeException");
                    serialVersionUID=-5696557788586220964LL;
                }

                virtual void initialize(){
                    JConstructor* cons=addConstructor(new JConstructor(JMalformedParameterizedTypeException::getClazz(),JModifier::PUBLIC,createJMalformedParameterizedTypeException));
                }

                virtual jcpp::lang::JClass* getSuperclass(){
                    return JRuntimeException::getClazz();
                }
            };

            static jcpp::lang::JClass* clazz;

            jcpp::lang::JClass* JMalformedParameterizedTypeException::getClazz(){
                if (clazz==null){
                    clazz=new JMalformedParameterizedTypeExceptionClass();
                }
                return clazz;
            }

            JMalformedParameterizedTypeException::JMalformedParameterizedTypeException():JRuntimeException(getClazz()){
            }

            JMalformedParameterizedTypeException::JMalformedParameterizedTypeException(JString* message):JRuntimeException(getClazz()){
                setMessage(message);
            }

            JMalformedParameterizedTypeException::~JMalformedParameterizedTypeException(){
            }
        }
    }
}
