#include "jcpp/lang/JTypeNotPresentException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{
        class JTypeNotPresentExceptionClass : public jcpp::lang::JClass{
        protected:
            static JObject* createJTypeNotPresentException(jcpp::util::JList* args){
                return new JTypeNotPresentException();
            }

            static JObject* staticGetTypeName(JObject* object){
                JTypeNotPresentException* s=dynamic_cast<JTypeNotPresentException*>(object);
                return s->getTypeName();
            }

            static void staticSetTypeName(JObject* object,JObject* value){
                JTypeNotPresentException* s=dynamic_cast<JTypeNotPresentException*>(object);
                s->typeName=dynamic_cast<JString*>(value);
            }

            static JObject** adrTypeName(JObject* object){
                JTypeNotPresentException* s=dynamic_cast<JTypeNotPresentException*>(object);
                return (JObject**)(&s->typeName);
            }
        public:
            JTypeNotPresentExceptionClass():jcpp::lang::JClass(){
                canonicalName=new JString("java.lang.TypeNotPresentException");
                name=new JString("java.lang.TypeNotPresentException");
                simpleName=new JString("TypeNotPresentException");
                serialVersionUID=-5101214195716534496LL;
            }

            virtual void initialize(){
                addConstructor(new JConstructor(JTypeNotPresentException::getClazz(),JModifier::PUBLIC,createJTypeNotPresentException));

                addField(new JField(new JString("typeName"),JString::getClazz(),this,staticGetTypeName,staticSetTypeName,adrTypeName));
            }

            virtual jcpp::lang::JClass* getSuperclass(){
                return JRuntimeException::getClazz();
            }
        };

        static jcpp::lang::JClass* clazz;

        jcpp::lang::JClass* JTypeNotPresentException::getClazz(){
            if (clazz==null){
                clazz=new JTypeNotPresentExceptionClass();
            }
            return clazz;
        }

        JTypeNotPresentException::JTypeNotPresentException():JRuntimeException(getClazz()){
        }

        JTypeNotPresentException::JTypeNotPresentException(jcpp::lang::JClass* _class):JRuntimeException(_class){
        }

        JTypeNotPresentException::JTypeNotPresentException(JString* typeName,JString* message):JRuntimeException(getClazz()){
            this->typeName=typeName;
            setMessage(message);
        }

        JString* JTypeNotPresentException::getTypeName(){
            return typeName;
        }

        JTypeNotPresentException::~JTypeNotPresentException(){
        }
    }
}

