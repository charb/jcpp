#include "jcpp/lang/JFloat.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/io/JSerializable.h"
#include "jcpp/lang/JByte.h"
#include "jcpp/lang/JStringBuilder.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;
using namespace jcpp::io;

namespace jcpp{
    namespace lang{

        jint JFloat::hashCode(jfloat f){
            return (jint)f;
        }

        jint JFloat::compare(jfloat f1,jfloat f2){
            return f1-f2;
        }

        JFloat* JFloat::valueOf(JString* s){
        	return new JFloat(s->getNativeString().toJfloat());
        }

        JString* JFloat::toString(jfloat d){
        	return new JString(NativeString::valueOf(d));
        }

        jfloat JFloat::MIN_VALUE = JFLOAT_MIN_POSITIVE;

        jfloat JFloat::MAX_VALUE = JFLOAT_MAX;

        jint JFloat::SIZE = 32;

        jint JFloat::BYTES = SIZE / JByte::SIZE;

        jcpp::lang::JClass* JFloat::TYPE = JPrimitiveFloat::getClazz();

        JFloat::JFloat(jfloat value):JNumber(getClazz()){
            this->value=new JPrimitiveFloat(value);
        }

        JFloat::JFloat():JNumber(getClazz()){
            this->value=new JPrimitiveFloat(0);
        }

        jbool JFloat::equals(JObject* other){
            if ((other != null) && other->getClass()==getClazz()){
                JFloat* s=dynamic_cast<JFloat*>(other);
                return value->equals(s->value);
            }
            return false;
        }

        void JFloat::set(jfloat value){
            this->value->set(value);
        }

        jfloat JFloat::get(){
            return value->get();
        }

        jbyte JFloat::byteValue(){
            return (jbyte)value->get();
        }

        jshort JFloat::shortValue(){
            return (jshort)value->get();
        }

        jint JFloat::intValue(){
            return (jint)value->get();
        }

        jlong JFloat::longValue(){
            return (jlong)value->get();
        }

        jfloat JFloat::floatValue(){
            return value->get();
        }

        jdouble JFloat::doubleValue(){
            return (jdouble)value->get();
        }

        void JFloat::setPrimitiveFloat(JPrimitiveFloat* value){
            this->value=value;
        }

        JPrimitiveFloat* JFloat::getPrimitiveFloat(){
            return value;
        }

        jint JFloat::compareTo(JObject *o){
            JFloat* f=dynamic_cast<JFloat*>(o);
            return compare(get(),f->get());
        }

        jint JFloat::hashCode(){
            return hashCode(value->get());
        }

        JString* JFloat::toString(){
            JStringBuilder* builder=new JStringBuilder();
            builder->append(value->get());
            return builder->toString();
        }

        JFloat::~JFloat(){
        }
    }
}
