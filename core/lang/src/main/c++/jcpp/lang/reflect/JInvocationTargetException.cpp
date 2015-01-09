#include "jcpp/lang/reflect/JInvocationTargetException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{
        namespace reflect{
            class JInvocationTargetExceptionClass : public jcpp::lang::JClass{
            protected:
                static JObject* createJInvocationTargetException(jcpp::util::JList* args){
                    return new JInvocationTargetException();
                }

                static JObject* staticGetTarget(JObject* object){
                    JInvocationTargetException* b=dynamic_cast<JInvocationTargetException*>(object);
                    return b->getTargetException();
                }

                static void staticSetTarget(JObject* object,JObject* value){
                    JInvocationTargetException* b=dynamic_cast<JInvocationTargetException*>(object);
                    b->target=dynamic_cast<JThrowable*>(value);
                }

                static JObject** adrTarget(JObject* object){
                    JInvocationTargetException* b=dynamic_cast<JInvocationTargetException*>(object);
                    return (JObject**)(&b->target);
                }

            public:
                JInvocationTargetExceptionClass():jcpp::lang::JClass(){
                    canonicalName=new JString("java.lang.reflect.InvocationTargetException");
                    name=new JString("java.lang.reflect.InvocationTargetException");
                    simpleName=new JString("InvocationTargetException");
                    serialVersionUID=4085088731926701167LL;
                }

                virtual void initialize(){
                    addConstructor(new JConstructor(JInvocationTargetException::getClazz(),JModifier::PUBLIC,createJInvocationTargetException));

                    addField(new JField(new JString("target"),JThrowable::getClazz(),this,staticGetTarget,staticSetTarget,adrTarget));
                }

                virtual jcpp::lang::JClass* getSuperclass(){
                    return JReflectiveOperationException::getClazz();
                }
            };

            static jcpp::lang::JClass* clazz;

            jcpp::lang::JClass* JInvocationTargetException::getClazz(){
                if (clazz==null){
                    clazz=new JInvocationTargetExceptionClass();
                }
                return clazz;
            }

            JInvocationTargetException::JInvocationTargetException():JReflectiveOperationException(getClazz()){
                target=null;
            }

            JInvocationTargetException::JInvocationTargetException(JThrowable* target):JReflectiveOperationException(getClazz()){
                this->target=target;
            }

            JInvocationTargetException::JInvocationTargetException(JThrowable* target,JString* message):JReflectiveOperationException(getClazz()){
                this->target=target;
                setMessage(message);
            }

            JThrowable* JInvocationTargetException::getTargetException(){
                return target;
            }

            JInvocationTargetException::~JInvocationTargetException(){
            }
        }
    }
}
