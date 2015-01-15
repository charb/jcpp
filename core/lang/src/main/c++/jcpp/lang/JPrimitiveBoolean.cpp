#include "jcpp/lang/JPrimitiveBoolean.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JString.h"
#include "jcpp/lang/JBoolean.h"
#include "jcpp/io/JSerializable.h"

using namespace jcpp::io;

namespace jcpp{
    namespace lang{

        JPrimitiveBoolean::JPrimitiveBoolean(jbool value):JObject(getClazz()){
            this->value=value;
        }

        JPrimitiveBoolean::JPrimitiveBoolean():JObject(getClazz()){
            this->value=false;
        }

        jbool JPrimitiveBoolean::equals(JObject* other){
            if ((other == null) || other->getClass()!=getClazz()){
                return false;
            }
            JPrimitiveBoolean* s=dynamic_cast<JPrimitiveBoolean*>(other);
            return value==s->value;
        }

        void JPrimitiveBoolean::set(jbool value){
            this->value=value;
        }

        jbool JPrimitiveBoolean::get(){
            return value;
        }

        jint JPrimitiveBoolean::compareTo(JObject* o){
            JPrimitiveBoolean* b=dynamic_cast<JPrimitiveBoolean*>(o);
            return (get() == b->get()) ? 0 : (get() ? 1 : -1);
        }

        jint JPrimitiveBoolean::hashCode(){
            return (value ? 1231 : 1237);
        }

        JString* JPrimitiveBoolean::toString(){
            return (value? JBoolean::TRUE_STRING : JBoolean::FALSE_STRING);
        }

        JPrimitiveBoolean::~JPrimitiveBoolean(){
        }
    }
}
