#include "jcpp/lang/JShort.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/io/JSerializable.h"
#include "jcpp/lang/JPrimitiveShort.h"
#include "jcpp/lang/JByte.h"
#include "jcpp/lang/JStringBuilder.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;
using namespace jcpp::io;

namespace jcpp{
    namespace lang{

        jint JShort::hashCode(jshort s){
            return (jint)s;
        }

        jint JShort::compare(jshort x, jshort y){
            return x-y;
        }

        jshort JShort::MIN_VALUE = JSHORT_MIN;

        jshort JShort::MAX_VALUE = JSHORT_MAX;

        jint JShort::SIZE = 16;

        jint JShort::BYTES = SIZE / JByte::SIZE;

        jcpp::lang::JClass* JShort::TYPE = JPrimitiveShort::getClazz();

        JShort::JShort(jshort value):JNumber(getClazz()){
            this->value=new JPrimitiveShort(value);
        }

        JShort::JShort():JNumber(getClazz()){
            this->value=new JPrimitiveShort(0);
        }

        jint JShort::compareTo(JObject* o){
            JShort* s=dynamic_cast<JShort*>(o);
            return compare(get(),s->get());
        }

        jbool JShort::equals(JObject* other){
            if ((other != null) && other->getClass()==getClazz()){
                JShort* s=dynamic_cast<JShort*>(other);
                return value->equals(s->value);
            }
            return false;
        }

        void JShort::set(jshort value){
            this->value->set(value);
        }

        jshort JShort::get(){
            return value->get();
        }

        jbyte JShort::byteValue(){
            return (jbyte)value->get();
        }

        jshort JShort::shortValue(){
            return value->get();
        }

        jint JShort::intValue(){
            return (jint)value->get();
        }

        jlong JShort::longValue(){
            return (jlong)value->get();
        }

        jfloat JShort::floatValue(){
            return (jfloat)value->get();
        }

        jdouble JShort::doubleValue(){
            return (jdouble)value->get();
        }

        void JShort::setPrimitiveShort(JPrimitiveShort* value){
            this->value=value;
        }

        JPrimitiveShort* JShort::getPrimitiveShort(){
            return value;
        }

        jint JShort::hashCode(){
            return hashCode(value->get());
        }

        JString* JShort::toString(){
            JStringBuilder* builder=new JStringBuilder();
            builder->append(value->get());
            return builder->toString();
        }

        JShort::~JShort(){
        }
    }
}
