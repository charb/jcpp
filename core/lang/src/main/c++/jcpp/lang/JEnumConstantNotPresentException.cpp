#include "jcpp/lang/JEnumConstantNotPresentException.h"
#include "jcpp/lang/reflect/JField.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{
        class JEnumConstantNotPresentExceptionClass : public jcpp::lang::JClass{
        protected:
            static JObject* createJEnumConstantNotPresentException(jcpp::util::JList* args){
                return new JEnumConstantNotPresentException();
            }

            static JObject* staticGetEnumType(JObject* object){
                JEnumConstantNotPresentException* s=dynamic_cast<JEnumConstantNotPresentException*>(object);
                return s->getEnumType();
            }

            static void staticSetEnumType(JObject* object,JObject* value){
                JEnumConstantNotPresentException* s=dynamic_cast<JEnumConstantNotPresentException*>(object);
                s->enumType=dynamic_cast<jcpp::lang::JClass*>(value);
            }

            static JObject** adrEnumType(JObject* object){
                JEnumConstantNotPresentException* s=dynamic_cast<JEnumConstantNotPresentException*>(object);
                return (JObject**)(&s->enumType);
            }

            static JObject* staticGetConstantName(JObject* object){
                JEnumConstantNotPresentException* s=dynamic_cast<JEnumConstantNotPresentException*>(object);
                return s->getConstantName();
            }

            static void staticSetConstantName(JObject* object,JObject* value){
                JEnumConstantNotPresentException* s=dynamic_cast<JEnumConstantNotPresentException*>(object);
                s->constantName=dynamic_cast<JString*>(value);
            }

            static JObject** adrConstantName(JObject* object){
                JEnumConstantNotPresentException* s=dynamic_cast<JEnumConstantNotPresentException*>(object);
                return (JObject**)(&s->constantName);
            }

        public:
            JEnumConstantNotPresentExceptionClass():jcpp::lang::JClass(){
                canonicalName=new JString("java.lang.EnumConstantNotPresentException");
                name=new JString("java.lang.EnumConstantNotPresentException");
                simpleName=new JString("EnumConstantNotPresentException");
                serialVersionUID=-6046998521960521108LL;
            }

            virtual void initialize(){
                JConstructor* cons=addConstructor(new JConstructor(JEnumConstantNotPresentException::getClazz(),JModifier::PUBLIC,createJEnumConstantNotPresentException));

                addField(new JField(new JString("enumType"),jcpp::lang::JClass::getClazz(),this,staticGetEnumType,staticSetEnumType,adrEnumType));
                addField(new JField(new JString("constantName"),JString::getClazz(),this,staticGetConstantName,staticSetConstantName,adrConstantName));
            }

            virtual jcpp::lang::JClass* getSuperclass(){
                return JRuntimeException::getClazz();
            }
        };

        static jcpp::lang::JClass* clazz;

        jcpp::lang::JClass* JEnumConstantNotPresentException::getClazz(){
            if (clazz==null){
                clazz=new JEnumConstantNotPresentExceptionClass();
            }
            return clazz;
        }

        JEnumConstantNotPresentException::JEnumConstantNotPresentException():JRuntimeException(getClazz()){
            this->enumType=null;
            this->constantName=null;
        }

        JEnumConstantNotPresentException::JEnumConstantNotPresentException(jcpp::lang::JClass* enumType, JString* constantName):JRuntimeException(getClazz()){
            this->enumType=enumType;
            this->constantName=constantName;
        }

        jcpp::lang::JClass* JEnumConstantNotPresentException::getEnumType(){
            return enumType;
        }

        JString* JEnumConstantNotPresentException::getConstantName(){
            return constantName;
        }

        JEnumConstantNotPresentException::~JEnumConstantNotPresentException(){
        }
    }
}

