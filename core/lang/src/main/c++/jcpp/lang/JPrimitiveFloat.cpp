#include "jcpp/lang/JPrimitiveFloat.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JStringBuilder.h"

namespace jcpp{
    namespace lang{
        class JPrimitiveFloatClass : public jcpp::lang::JClass{
          public:
            JPrimitiveFloatClass():jcpp::lang::JClass(){
                this->canonicalName=new JString("float");
                this->name=new JString("float");
                this->simpleName=new JString("float");
                this->bIsPrimitive=true;
            }

            virtual void initialize(){
                addInterface(JComparable::getClazz());
                addInterface(JSerializable::getClazz());
            }

            virtual jcpp::lang::JClass* getSuperclass(){
                return JObject::getClazz();
            }
        };

        static jcpp::lang::JClass* clazz;

        jcpp::lang::JClass* JPrimitiveFloat::getClazz(){
            if (clazz==null){
                clazz=new JPrimitiveFloatClass();
            }
            return clazz;
        }

        JPrimitiveFloat::JPrimitiveFloat(jfloat value):JObject(getClazz()){
            this->value=value;
        }

        JPrimitiveFloat::JPrimitiveFloat():JObject(getClazz()){
            this->value=0;
        }

        jint JPrimitiveFloat::compareTo(JObject* o){
            JPrimitiveFloat* s=dynamic_cast<JPrimitiveFloat*>(o);
            return get()-s->get();
        }

        jbool JPrimitiveFloat::equals(JObject* other){
            if ((other == null) || other->getClass()!=getClazz()){
                return false;
            }
            JPrimitiveFloat* s=dynamic_cast<JPrimitiveFloat*>(other);
            return value==s->value;
        }

        void JPrimitiveFloat::set(jfloat value){
            this->value=value;
        }

        jfloat JPrimitiveFloat::get(){
            return value;
        }

        jint JPrimitiveFloat::hashCode(){
            return (jint)value;
        }

        JString* JPrimitiveFloat::toString(){
            JStringBuilder* builder=new JStringBuilder();
            builder->append(value);
            return builder->toString();
        }

        JPrimitiveFloat::~JPrimitiveFloat(){
        }
    }
}
