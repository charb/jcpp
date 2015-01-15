#include "jcpp/lang/JPrimitiveByte.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JString.h"
#include "jcpp/lang/JStringBuilder.h"

namespace jcpp{
    namespace lang{

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
