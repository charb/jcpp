#include "jcpp/lang/JStackTraceElement.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/io/JSerializable.h"
#include "jcpp/lang/JPrimitiveInt.h"
#include "jcpp/lang/reflect/JField.h"
#include "jcpp/lang/JStringBuilder.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/JSystem.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{
        class JStackTraceElementClass : public jcpp::lang::JClass{
            protected:
                static JObject* createJStackTraceElement(jcpp::util::JList* args){
                    return new JStackTraceElement();
                }

                static JObject* staticGetDeclaringClass(JObject* object){
                    JStackTraceElement* e=dynamic_cast<JStackTraceElement*>(object);
                    return e->getDeclaringClass();
                }

                static void staticSetDeclaringClass(JObject* object,JObject* value){
                    JStackTraceElement* e=dynamic_cast<JStackTraceElement*>(object);
                    e->setDeclaringClass(dynamic_cast<JString*>(value));
                }

                static JObject** adrDeclaringClass(JObject* object){
                    JStackTraceElement* e=dynamic_cast<JStackTraceElement*>(object);
                    return (JObject**)&e->declaringClass;
                }

                static JObject* staticGetMethodName(JObject* object){
                    JStackTraceElement* e=dynamic_cast<JStackTraceElement*>(object);
                    return e->getMethodName();
                }

                static void staticSetMethodName(JObject* object,JObject* value){
                    JStackTraceElement* e=dynamic_cast<JStackTraceElement*>(object);
                    e->setMethodName(dynamic_cast<JString*>(value));
                }

                static JObject** adrMethodName(JObject* object){
                    JStackTraceElement* e=dynamic_cast<JStackTraceElement*>(object);
                    return (JObject**)&e->methodName;
                }

                static JObject* staticGetFileName(JObject* object){
                    JStackTraceElement* e=dynamic_cast<JStackTraceElement*>(object);
                    return e->getFileName();
                }

                static void staticSetFileName(JObject* object,JObject* value){
                    JStackTraceElement* e=dynamic_cast<JStackTraceElement*>(object);
                    e->setFileName(dynamic_cast<JString*>(value));
                }

                static JObject** adrFileName(JObject* object){
                    JStackTraceElement* e=dynamic_cast<JStackTraceElement*>(object);
                    return (JObject**)&e->fileName;
                }

                static JObject* staticGetLineNumber(JObject* object){
                    JStackTraceElement* e=dynamic_cast<JStackTraceElement*>(object);
                    return e->getPLineNumber();
                }

                static void staticSetLineNumber(JObject* object,JObject* value){
                    JStackTraceElement* e=dynamic_cast<JStackTraceElement*>(object);
                    e->setPLineNumber(dynamic_cast<JPrimitiveInt*>(value));
                }

                static JObject** adrLineNumber(JObject* object){
                    JStackTraceElement* e=dynamic_cast<JStackTraceElement*>(object);
                    return (JObject**)&e->lineNumber;
                }

          public:
            JStackTraceElementClass():jcpp::lang::JClass(){
                this->canonicalName=new JString("java.lang.StackTraceElement");
                this->name=new JString("java.lang.StackTraceElement");
                this->simpleName=new JString("StackTraceElement");
                this->serialVersionUID=6992337162326171013ULL;
            }

            virtual void initialize(){
                addInterface(JSerializable::getClazz());

                addConstructor(new JConstructor(JStackTraceElement::getClazz(),JModifier::PUBLIC,createJStackTraceElement));

                addField(new JField(new JString("declaringClass"),JString::getClazz(),this,staticGetDeclaringClass,staticSetDeclaringClass,adrDeclaringClass));
                addField(new JField(new JString("methodName"),JString::getClazz(),this,staticGetMethodName,staticSetMethodName,adrMethodName));
                addField(new JField(new JString("fileName"),JString::getClazz(),this,staticGetFileName,staticSetFileName,adrFileName));
                addField(new JField(new JString("lineNumber"),JPrimitiveInt::getClazz(),this,staticGetLineNumber,staticSetLineNumber,adrLineNumber));
            }

            virtual jcpp::lang::JClass* getSuperclass(){
                return JObject::getClazz();
            }
        };

        static jcpp::lang::JClass* clazz = null;

        jcpp::lang::JClass* JStackTraceElement::getClazz(){
            if (clazz==null){
                clazz=new JStackTraceElementClass();
            }
            return clazz;
        }

        JStackTraceElement::JStackTraceElement():JObject(getClazz()){
            declaringClass=null;
            methodName=null;
            fileName=null;
            lineNumber=null;
        }

        JStackTraceElement::JStackTraceElement(JString* declaringClass,JString* methodName,JString* fileName,jint lineNumber):JObject(getClazz()){
            this->declaringClass=declaringClass;
            this->methodName=methodName;
            this->fileName=fileName;
            this->lineNumber=new JPrimitiveInt(lineNumber);
        }

        jbool JStackTraceElement::equals(JObject* other){
            if ((other == null) || other->getClass()!=JStackTraceElement::getClazz()){
                return false;
            }
            JStackTraceElement* se=dynamic_cast<JStackTraceElement*>(other);
            jbool eq=true;
            if (se->declaringClass!=null && declaringClass!=null){
                eq=se->declaringClass->equals(declaringClass);
            }else{
                eq=se->declaringClass==null && declaringClass==null;
            }
            if (!eq){
                return false;
            }
            if (se->methodName!=null && methodName!=null){
                eq=se->methodName->equals(methodName);
            }else{
                eq=se->methodName==null && methodName==null;
            }
            if (!eq){
                return false;
            }
            if (se->fileName!=null && fileName!=null){
                eq=se->fileName->equals(fileName);
            }else{
                eq=se->fileName==null && fileName==null;
            }
            if (!eq){
                return false;
            }
            if (se->lineNumber!=null && lineNumber!=null){
                eq=se->lineNumber->equals(lineNumber);
            }else{
                eq=se->lineNumber==null && lineNumber==null;
            }
            if (!eq){
                return false;
            }else{
                return true;
            }
        }

        JString* JStackTraceElement::getDeclaringClass(){
            return declaringClass;
        }

        void JStackTraceElement::setDeclaringClass(JString* declaringClass){
            this->declaringClass=declaringClass;
        }

        JString* JStackTraceElement::getMethodName(){
            return methodName;
        }

        void JStackTraceElement::setMethodName(JString* methodName){
            this->methodName=methodName;
        }

        JString* JStackTraceElement::getFileName(){
            return fileName;
        }

        void JStackTraceElement::setFileName(JString* fileName){
            this->fileName=fileName;
        }

        JPrimitiveInt* JStackTraceElement::getPLineNumber(){
            return lineNumber;
        }

        void JStackTraceElement::setPLineNumber(JPrimitiveInt* lineNumber){
            this->lineNumber=lineNumber;
        }

        jint JStackTraceElement::getLineNumber(){
            return lineNumber->get();
        }

        void JStackTraceElement::setLineNumber(jint lineNumber){
            this->lineNumber->set(lineNumber);
        }

        jint JStackTraceElement::hashCode(){
            jint result = 31*declaringClass->hashCode() + methodName->hashCode();
            result = 31*result + fileName->hashCode();
            result = 31*result + lineNumber->hashCode();
            return result;
        }

        JString* JStackTraceElement::toString(){
            JStringBuilder* builder=new JStringBuilder();
            if (getDeclaringClass()!=null){
                builder->append(getDeclaringClass())->append(".");
            }
            if (getMethodName()!=null){
                builder->append(getMethodName());
            }
            if (getFileName()!=null){
                builder->append("(")->append(getFileName())->append(":");
            }
            if (getPLineNumber()!=null){
                builder->append(getPLineNumber()->toString());
            }
            builder->append(")");
            return builder->toString();
        }

        JStackTraceElement::~JStackTraceElement(){
        }
    }
}

