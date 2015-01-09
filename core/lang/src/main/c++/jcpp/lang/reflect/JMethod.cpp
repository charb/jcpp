#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/JString.h"
#include "jcpp/lang/JStringBuilder.h"
#include "jcpp/lang/JClassLoader.h"
#include "jcpp/util/JList.h"
#include "jcpp/lang/JStringBuilder.h"

namespace jcpp{
    namespace lang{
        namespace reflect{

            class JMethodClass : public jcpp::lang::JClass{
                public:
                    JMethodClass():jcpp::lang::JClass(){
                        canonicalName=new JString("java.lang.reflect.Method");
                        name=new JString("java.lang.reflect.Method");
                        simpleName=new JString("Method");
                    }

                    virtual jcpp::lang::JClass* getSuperclass(){
                        return JExecutable::getClazz();
                    }
            };

            static jcpp::lang::JClass* clazz;

            jcpp::lang::JClass* JMethod::getClazz(){
                if (clazz==null){
                    clazz= new JMethodClass();
                }
                return clazz;
            }

            JMethod::JMethod(JString* name,jcpp::lang::JClass* declaringClass,jcpp::lang::JClass* returnType,invocation inv):JExecutable(getClazz()){
                this->name=name;
                this->declaringClass=declaringClass;
                this->returnType=returnType;
                this->inv=inv;
            }

            jbool JMethod::equals(JObject* obj) {
                if (obj != null && !getClazz()->equals(obj->getClass())) {
                    JMethod* other = dynamic_cast<JMethod*>(obj);
                    if (getDeclaringClass()->equals(other->getDeclaringClass()) && getName()->equals(other->getName())) {
                        if (!returnType->equals(other->getReturnType())){
                            return false;
                        }
                        return equalParamTypes(parameterTypes, other->parameterTypes);
                    }
                }
                return false;
            }

            jcpp::lang::JClass* JMethod::getReturnType(){
                return returnType;
            }

            jint JMethod::hashCode() {
                return getDeclaringClass()->getName()->hashCode()^ getName()->hashCode();
            }

            JObject* JMethod::invoke(JObject* object, JList* args){
                return inv(object,args);
            }

            JMethod* JMethod::addAnnotation(JAnnotation* ann){
                JExecutable::addAnnotation(ann);
                return this;
            }

            JMethod* JMethod::addParameterType(jcpp::lang::JClass* type){
                JExecutable::addParameterType(type);
                return this;
            }

            JMethod* JMethod::addParameterAnnotation(jint index,JAnnotation* ann){
                JExecutable::addParameterAnnotation(index,ann);
                return this;
            }

            void JMethod::specificToStringHeader(JStringBuilder* sb) {
                sb->append(getReturnType()->getTypeName())->append(' ');
                sb->append(getDeclaringClass()->getTypeName())->append('.');
                sb->append(getName());
            }

            void JMethod::setPublic(){
                JExecutable::setPublic();
            }
             
            void JMethod::setPrivate() {
            	JExecutable::setPrivate();
            }

            void JMethod::setProtected() {
            	JExecutable::setProtected();
            }

            void JMethod::setStatic(){
                JExecutable::setStatic();
            }
           
            JString* JMethod::toString(){
                JStringBuilder* builder=new JStringBuilder();
                builder->append(returnType->getName())->append(" ")->append(declaringClass->toString());
                builder->append(".")->append(name);
                if (parameterTypes!=null){
                    builder->append("(");
                    for (jint i=0;i<parameterTypes->size();i++){
                        jcpp::lang::JClass* param=dynamic_cast<jcpp::lang::JClass*>(parameterTypes->get(i));
                        builder->append(param->getName())->append(",");
                    }
                }
                return builder->toString();
            }

            JMethod::~JMethod(){
            }
        }
    }
}
