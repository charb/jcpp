#include "jcpp/lang/reflect/JUndeclaredThrowableException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{
        namespace reflect{
            class JUndeclaredThrowableExceptionClass : public jcpp::lang::JClass{
            protected:
                static JObject* createJUndeclaredThrowableException(jcpp::util::JList* args){
                    return new JUndeclaredThrowableException();
                }

                static JObject* staticGetUndeclaredThrowable(JObject* object){
                    JUndeclaredThrowableException* b=dynamic_cast<JUndeclaredThrowableException*>(object);
                    return b->undeclaredThrowable;
                }

                static void staticSetUndeclaredThrowable(JObject* object,JObject* value){
                    JUndeclaredThrowableException* b=dynamic_cast<JUndeclaredThrowableException*>(object);
                    b->undeclaredThrowable=dynamic_cast<JThrowable*>(value);
                }

                static JObject** adrUndeclaredThrowable(JObject* object){
                    JUndeclaredThrowableException* b=dynamic_cast<JUndeclaredThrowableException*>(object);
                    return (JObject**)(&b->undeclaredThrowable);
                }

            public:
                JUndeclaredThrowableExceptionClass():jcpp::lang::JClass(){
                    canonicalName=new JString("java.lang.reflect.UndeclaredThrowableException");
                    name=new JString("java.lang.reflect.UndeclaredThrowableException");
                    simpleName=new JString("UndeclaredThrowableException");
                    serialVersionUID=330127114055056639LL;
                }

                virtual void initialize(){
                    JConstructor* cons=addConstructor(new JConstructor(JUndeclaredThrowableException::getClazz(),JModifier::PUBLIC,createJUndeclaredThrowableException));

                    addField(new JField(new JString("undeclaredThrowable"),JThrowable::getClazz(),this,staticGetUndeclaredThrowable,staticSetUndeclaredThrowable,adrUndeclaredThrowable));
                }

                virtual jcpp::lang::JClass* getSuperclass(){
                    return JRuntimeException::getClazz();
                }
            };

            static jcpp::lang::JClass* clazz;

            jcpp::lang::JClass* JUndeclaredThrowableException::getClazz(){
                if (clazz==null){
                    clazz=new JUndeclaredThrowableExceptionClass();
                }
                return clazz;
            }

            JUndeclaredThrowableException::JUndeclaredThrowableException():JRuntimeException(getClazz()){
                undeclaredThrowable=null;
            }

            JUndeclaredThrowableException::JUndeclaredThrowableException(JThrowable* undeclaredThrowable):JRuntimeException(getClazz()){
                this->undeclaredThrowable=undeclaredThrowable;
            }

            JUndeclaredThrowableException::JUndeclaredThrowableException(JThrowable* undeclaredThrowable,JString* message):JRuntimeException(getClazz()){
                this->undeclaredThrowable=undeclaredThrowable;
                setMessage(message);
            }

            JThrowable* JUndeclaredThrowableException::getUndeclaredThrowable(){
                return undeclaredThrowable;
            }

            JUndeclaredThrowableException::~JUndeclaredThrowableException(){
            }
        }
    }
}
