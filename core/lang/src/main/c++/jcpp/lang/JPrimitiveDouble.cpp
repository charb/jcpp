#include "jcpp/lang/JPrimitiveDouble.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JStringBuilder.h"

namespace jcpp{
    namespace lang{

        JPrimitiveDouble::JPrimitiveDouble(jdouble value):JObject(getClazz()){
            this->value=value;
        }

        JPrimitiveDouble::JPrimitiveDouble():JObject(getClazz()){
            this->value=0;
        }

        jint JPrimitiveDouble::compareTo(JObject* o){
            JPrimitiveDouble* s=dynamic_cast<JPrimitiveDouble*>(o);
            return get()-s->get();
        }

        jbool JPrimitiveDouble::equals(JObject* other){
            if ((other == null) || other->getClass()!=getClazz()){
                return false;
            }
            JPrimitiveDouble* s=dynamic_cast<JPrimitiveDouble*>(other);
            return value==s->value;
        }

        void JPrimitiveDouble::set(jdouble value){
            this->value=value;
        }

        jdouble JPrimitiveDouble::get(){
            return value;
        }

        jint JPrimitiveDouble::hashCode(){
            return (jint)value;
        }

        JString* JPrimitiveDouble::toString(){
            JStringBuilder* builder=new JStringBuilder();
            builder->append(value);
            return builder->toString();
        }

        JPrimitiveDouble::~JPrimitiveDouble(){
        }
    }
}

