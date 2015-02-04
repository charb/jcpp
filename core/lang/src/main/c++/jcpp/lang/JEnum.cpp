#include "jcpp/lang/JEnum.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JClassCastException.h"
#include "jcpp/lang/JNullPointerException.h"
#include "jcpp/lang/JIllegalArgumentException.h"
#include "jcpp/lang/JStringBuilder.h"

namespace jcpp{
    namespace lang{

    	JEnum::JEnumClass::JEnumClass(){
			this->canonicalName=new JString("java.lang.Enum");
			this->name=new JString("java.lang.Enum");
			this->simpleName=new JString("Enum");
			this->bIsEnum=true;
		}

		void JEnum::JEnumClass::initialize(){
			addInterface(JComparable::getClazz());
			addInterface(JSerializable::getClazz());
		}

		jcpp::lang::JClass* JEnum::JEnumClass::getSuperclass(){
			return JObject::getClazz();
		}

        JEnum::JEnum(JEnumClass* _class,JString* name,JPrimitiveInt* ordinal):JObject(_class){
            this->name=name;
            this->ord=ordinal;
        }

        static jcpp::lang::JClass* clazz;

        jcpp::lang::JClass* JEnum::getClazz(){
            if (clazz==null){
                clazz=new JEnumClass();
            }
            return clazz;
        }

        JEnum* JEnum::valueOf(jcpp::lang::JClass* enumType,JString* name){
            if (name == null){
                throw new JNullPointerException(new JString("Name is null"));
            }
            JEnum* result = enumType->valueOf(name);
            if (result != null){
                return result;
            }
            JStringBuilder* builder=new JStringBuilder();
            builder->append("No enum constant ")->append(enumType->getCanonicalName())->append(".")->append(name);
            throw new JIllegalArgumentException(builder->toString());    
        }

        JString* JEnum::getName(){
            return name;
        }

        jint JEnum::ordinal(){
            return ord->get();
        }

        jcpp::lang::JClass* JEnum::getDeclaringClass(){
            jcpp::lang::JClass* clazz = getClass();
            jcpp::lang::JClass* zuper = clazz->getSuperclass();
            return (zuper == JEnum::getClazz()) ? clazz : zuper;
        }

        jint JEnum::compareTo(JObject* o){
            JEnum* e=dynamic_cast<JEnum*>(o);
            if (!getClass()->equals(e->getClass()) && !this->getDeclaringClass()->equals(e->getDeclaringClass())){
                throw new JClassCastException();
            }
            return ord - e->ord;
        }

        jbool JEnum::equals(JObject* other){
            if ((other != null) && other->getClass()==getClass()){
                JEnum* s=dynamic_cast<JEnum*>(other);
                return name->equals(s->name) && ord->equals(s->ord);
            }
            return false;
        }

        jint JEnum::hashCode(){
            return JObject::hashCode();
        }

        JString* JEnum::toString(){
            return name;
        }

        JEnum::~JEnum() {
        }
    }
}
