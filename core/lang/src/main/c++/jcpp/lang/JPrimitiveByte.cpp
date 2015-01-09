#include "jcpp/lang/JPrimitiveByte.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JString.h"
#include "jcpp/lang/JStringBuilder.h"

namespace jcpp{
    namespace lang{
        class JPrimitiveByteClass : public jcpp::lang::JClass{
          public:
            JPrimitiveByteClass():jcpp::lang::JClass(){
                this->canonicalName=new JString("byte");
                this->name=new JString("byte");
                this->simpleName=new JString("byte");
                this->bIsPrimitive=true;
            }

            virtual void initialize(){
                addInterface(JComparable::getClazz());
            }

            virtual jcpp::lang::JClass* getSuperclass(){
                return JObject::getClazz();
            }
        };

        static jcpp::lang::JClass* clazz;

        jcpp::lang::JClass* JPrimitiveByte::getClazz(){
            if (clazz==null){
                clazz=new JPrimitiveByteClass();
            }
            return clazz;
        }

        JPrimitiveByte::JPrimitiveByte(jbyte value):JObject(getClazz()){
            this->value=value;
        }

        JPrimitiveByte::JPrimitiveByte():JObject(getClazz()){
            this->value=0;
        }

        void JPrimitiveByte::set(jbyte value){
            this->value=value;
        }

        jbyte JPrimitiveByte::get(){
            return value;
        }

        jint JPrimitiveByte::compareTo(JObject* o){
            JPrimitiveByte* b=dynamic_cast<JPrimitiveByte*>(o);
            return get()-b->get();
        }

        jbool JPrimitiveByte::equals(JObject* other){
            if ((other == null) || other->getClass()!=getClazz()){
                return false;
            }
            JPrimitiveByte* s=dynamic_cast<JPrimitiveByte*>(other);
            return value==s->value;
        }

        jint JPrimitiveByte::hashCode(){
            return (jint)value;
        }

        JString* JPrimitiveByte::toString(){
            JStringBuilder* builder=new JStringBuilder();
            builder->append(value);
            return builder->toString();
        }

        JPrimitiveByte::~JPrimitiveByte(){
        }
    }
}
