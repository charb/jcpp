#include "jcpp/lang/reflect/JField.h"
#include "jcpp/lang/reflect/JExecutable.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JString.h"
#include "jcpp/lang/JClassLoader.h"
#include "jcpp/util/JList.h"
#include "jcpp/util/JArrayList.h"
#include "jcpp/lang/JStringBuilder.h"
#include "jcpp/lang/JIllegalArgumentException.h"

namespace jcpp{
    namespace lang{
        namespace reflect{

            JExecutable::JExecutable():JAccessibleObject(JExecutable::getClazz()){
                modifiers=0;
                name=null;
                declaringClass=null;
                annotations=new JArrayList();
                parameterTypes=new JArrayList();
                parameterAnnotations=new JArrayList();
            }

            JExecutable::JExecutable(jcpp::lang::JClass* _class):JAccessibleObject(_class){
                modifiers=0;
                name=null;
                declaringClass=null;
                annotations=new JArrayList();
                parameterTypes=new JArrayList();
                parameterAnnotations=new JArrayList();
            }

            void JExecutable::setPublic(){
                modifiers|=JModifier::PUBLIC;
            }

            void JExecutable::setPrivate(){
            	modifiers|=JModifier::PRIVATE;
            }

            void JExecutable::setProtected(){
            	modifiers|=JModifier::PROTECTED;
            }
             
            void JExecutable::setStatic(){
                modifiers|=JModifier::STATIC;
            }

            void JExecutable::setFinal(){
            	modifiers|=JModifier::FINAL;
            }

            void JExecutable::setNative(){
            	modifiers|=JModifier::NATIVE;
            }

            void JExecutable::setAbstract(){
            	modifiers|=JModifier::ABSTRACT;
            }

            JExecutable* JExecutable::addAnnotation(JAnnotation* ann){
                annotations->add(dynamic_cast<JObject*>(ann));
                return this;
            }

            JExecutable* JExecutable::addParameterType(jcpp::lang::JClass* type){
                parameterTypes->add(type);
                parameterAnnotations->add(new JArrayList());
                return this;
            }

            JExecutable* JExecutable::addParameterAnnotation(jint index,JAnnotation* ann){
                JList* l=dynamic_cast<JList*>(parameterAnnotations->get(index));
                l->add(dynamic_cast<JObject*>(ann));
                return this;
            }

            jbool JExecutable::equalParamTypes(JList* params1, JList* params2) {
                if (params1->size() == params2->size()) {
                    for (jint i = 0; i < params1->size(); i++) {
                        if (!params1->get(i)->equals(params2->get(i))){
                            return false;
                        }
                    }
                    return true;
                }
                return false;
            }

            void JExecutable::checkArguments(JList* arguments){
                if (arguments==null || arguments->size()==0){
                    if (parameterTypes!=null && parameterTypes->size()>0){
                        throw new JIllegalArgumentException(new JString("Wrong arguments size"));
                    }
                }else{
                    if (arguments->size()!=parameterTypes->size()){
                        throw new JIllegalArgumentException(new JString("Wrong arguments size"));
                    }
                    for (jint i=0;i<arguments->size();i++){
                        jcpp::lang::JClass* t=dynamic_cast<jcpp::lang::JClass*>(parameterTypes->get(i));
                        JObject* o=arguments->get(i);
                        if (o!=null && !o->isInstanceOf(t)){
                            throw new JIllegalArgumentException(new JString("Wrong argument type"));
                        }
                    }
                }
            }

            void JExecutable::separateWithCommas(JList* types, JStringBuilder* sb) {
                for (jint j = 0; j < types->size(); j++) {
                    jcpp::lang::JClass* t=dynamic_cast<jcpp::lang::JClass*>(types->get(j));
                    sb->append(t->getTypeName());
                    if (j < (types->size() - 1)){
                        sb->append(",");
                    }
                }
            }

            void JExecutable::printModifiersIfNonzero(JStringBuilder* sb, jbool isDefault) {
                jint mod = getModifiers();
                sb->append(JModifier::toString(mod))->append(" ");
            }

            JString* JExecutable::sharedToString(jbool isDefault,JList* parameterTypes) {
                JStringBuilder* sb = new JStringBuilder();

                printModifiersIfNonzero(sb, isDefault);
                specificToStringHeader(sb);

                sb->append("(");
                separateWithCommas(parameterTypes, sb);
                sb->append(")");
                return sb->toString();
            }
                
            JAnnotation* JExecutable::getAnnotation(jcpp::lang::JClass* annotationClass){
                for (jint i=0;i<annotations->size();i++){
                    JAnnotation* ann=dynamic_cast<JAnnotation*>(annotations->get(i));
                    if (ann->annotationType()->equals(annotationClass)){
                        return ann;
                    }
                }
                return null;
            }

            jcpp::util::JList* JExecutable::getAnnotations(){
                return annotations;
            }

            jcpp::lang::JClass* JExecutable::getDeclaringClass(){
                return declaringClass;
            }

            jint JExecutable::getModifiers(){
                return modifiers;
            }

            JString* JExecutable::getName(){
                return name;
            }

            jcpp::util::JList* JExecutable::getParameterAnnotations(){
                return parameterAnnotations;
            }

            jint JExecutable::getParameterCount(){
                return parameterTypes->size();
            }

            jcpp::util::JList* JExecutable::getParameterTypes(){
                return parameterTypes;
            }

            JExecutable::~JExecutable(){
            }
        }
    }
}
