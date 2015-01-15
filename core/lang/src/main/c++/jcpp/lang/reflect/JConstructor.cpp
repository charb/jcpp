#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/JString.h"
#include "jcpp/lang/JStringBuilder.h"
#include "jcpp/lang/JClassLoader.h"
#include "jcpp/util/JList.h"
#include "jcpp/util/JMap.h"

using namespace jcpp::lang;
using namespace jcpp::util;

namespace jcpp{
    namespace lang{
        namespace reflect{

            JConstructor::JConstructor(jcpp::lang::JClass* declaringClass,jint modifiers,instantiator inst):JExecutable(getClazz()){
                this->declaringClass=declaringClass;
                this->name=declaringClass->getName();
                this->modifiers=modifiers;
                this->inst=inst;
            }

            JConstructor* JConstructor::addAnnotation(JAnnotation* ann){
                JExecutable::addAnnotation(ann);
                return this;
            }

            JConstructor* JConstructor::addParameterType(jcpp::lang::JClass* type){
                JExecutable::addParameterType(type);
                return this;
            }
                
            JConstructor* JConstructor::addParameterAnnotation(jint index,JAnnotation* ann){
                JExecutable::addParameterAnnotation(index,ann);
                return this;
            }

            jbool JConstructor::equals(JObject* obj){
                if (obj != null && obj->isInstanceOf(JConstructor::getClazz())) {
                    JConstructor* other = dynamic_cast<JConstructor*>(obj);
                    if (getDeclaringClass()->equals(other->getDeclaringClass())) {
                        return equalParamTypes(parameterTypes, other->parameterTypes);
                    }
                }
                return false;
            }

            jint JConstructor::hashCode(){
                return declaringClass->getName()->hashCode();
            }

            JObject* JConstructor::newInstance(JList* initargs){
                checkArguments(initargs);
                return inst(initargs);
            }

            void JConstructor::specificToStringHeader(JStringBuilder* sb) {
                sb->append(getDeclaringClass()->getTypeName());
            }

            JString* JConstructor::toString(){
                return sharedToString(false,parameterTypes);
            }

            JConstructor::~JConstructor(){
            }
        }
    }
}
