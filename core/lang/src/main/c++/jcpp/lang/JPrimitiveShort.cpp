#include "jcpp/lang/JPrimitiveShort.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JStringBuilder.h"

namespace jcpp{
    namespace lang{

        JPrimitiveShort::JPrimitiveShort(jshort value):JObject(getClazz()){
            this->value=value;
        }

        JPrimitiveShort::JPrimitiveShort():JObject(getClazz()){
            this->value=0;
        }

        jint JPrimitiveShort::compareTo(JObject* o){
            JPrimitiveShort* s=dynamic_cast<JPrimitiveShort*>(o);
            return get()-s->get();
        }

        jbool JPrimitiveShort::equals(JObject* other){
            if ((other == null) || other->getClass()!=getClazz()){
                return false;
            }
            JPrimitiveShort* s=dynamic_cast<JPrimitiveShort*>(other);
            return value==s->value;
        }

        void JPrimitiveShort::set(jshort value){
            this->value=value;
        }

        jshort JPrimitiveShort::get(){
            return value;
        }

        jint JPrimitiveShort::hashCode(){
            return (jint)value;
        }

        JString* JPrimitiveShort::toString(){
            JStringBuilder* builder=new JStringBuilder();
            builder->append(value);
            return builder->toString();
        }

        JPrimitiveShort::~JPrimitiveShort(){
        }
    }
}
