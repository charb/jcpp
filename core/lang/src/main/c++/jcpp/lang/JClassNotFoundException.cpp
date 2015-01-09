#include "jcpp/lang/JClassNotFoundException.h"
#include "jcpp/lang/reflect/JField.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/JSystem.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{
        class JClassNotFoundExceptionClass : public jcpp::lang::JClass{
        protected:
            static JObject* createJClassNotFoundException(jcpp::util::JList* args){
                return new JClassNotFoundException();
            }

            static JObject* staticGetException(JObject* object){
                JClassNotFoundException* th=dynamic_cast<JClassNotFoundException*>(object);
                return th->ex;
            }

            static void staticSetException(JObject* object,JObject* value){
                JClassNotFoundException* th=dynamic_cast<JClassNotFoundException*>(object);
                th->ex=dynamic_cast<JThrowable*>(value);
            }

            static JObject** adrException(JObject* object){
                JClassNotFoundException* th=dynamic_cast<JClassNotFoundException*>(object);
                return (JObject**)&th->ex;
            }

        public:
            JClassNotFoundExceptionClass():jcpp::lang::JClass(){
                canonicalName=new JString("java.lang.ClassNotFoundException");
                name=new JString("java.lang.ClassNotFoundException");
                simpleName=new JString("ClassNotFoundException");
                serialVersionUID=9176873029745254542LL;
            }

            virtual void initialize(){
                JConstructor* cons=addConstructor(new JConstructor(JClassNotFoundException::getClazz(),JModifier::PUBLIC,createJClassNotFoundException));
                
                addField(new JField(new JString("ex"),JThrowable::getClazz(),this,staticGetException,staticSetException,adrException));
            }

            virtual jcpp::lang::JClass* getSuperclass(){
                return JReflectiveOperationException::getClazz();
            }
        };

        static jcpp::lang::JClass* clazz;

        jcpp::lang::JClass* JClassNotFoundException::getClazz(){
            if (clazz==null){
                clazz=new JClassNotFoundExceptionClass();
            }
            return clazz;
        }

        JClassNotFoundException::JClassNotFoundException():JReflectiveOperationException(getClazz()){
            ex=null;
        }

        JClassNotFoundException::JClassNotFoundException(JString* message):JReflectiveOperationException(getClazz()){
            setMessage(message);
            ex=null;
        }

        void JClassNotFoundException::setCause(JThrowable* th){
            this->cause=th;
            this->ex=th;
        }

        JThrowable* JClassNotFoundException::getException(){
            return ex;
        }

        JThrowable* JClassNotFoundException::getCause(){
            return ex;
        }

        JClassNotFoundException::~JClassNotFoundException(){
        }
    }
}
