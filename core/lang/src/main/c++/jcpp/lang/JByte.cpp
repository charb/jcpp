#include "jcpp/lang/JByte.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/io/JSerializable.h"
#include "jcpp/lang/JString.h"
#include "jcpp/lang/JStringBuilder.h"
#include "jcpp/lang/reflect/JField.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;
using namespace jcpp::io;

namespace jcpp{
    namespace lang{

        jint JByte::hashCode(jbyte b){
            return (jint)b;
        }

        jint JByte::compare(jbyte x,jbyte y){
            return x-y;
        }

        jbyte JByte::MIN_VALUE= JBYTE_MIN;

        jbyte JByte::MAX_VALUE= JBYTE_MAX;

        jcpp::lang::JClass* JByte::TYPE = JPrimitiveByte::getClazz();

        jint JByte::toUnsignedInt(jbyte x){
            return ((jint) x) & 0xff;
        }

        jlong JByte::toUnsignedLong(jbyte x){
            return ((jlong) x) & 0xffL;
        }

        jint JByte::SIZE = 8;

        jint JByte::BYTES = SIZE / JByte::SIZE;

        JByte::JByte(jbyte value):JNumber(getClazz()){
            this->value=new JPrimitiveByte(value);
        }

        JByte::JByte():JNumber(getClazz()){
            this->value=new JPrimitiveByte(0);
        }

        jbool JByte::equals(JObject* other){
            if ((other == null) || other->getClass()!=getClazz()){
                return false;
            }
            JByte* b=dynamic_cast<JByte*>(other);
            return value->equals(b->value);
        }

        void JByte::set(jbyte value){
            this->value->set(value);
        }

        jbyte JByte::get(){
            return value->get();
        }

        jbyte JByte::byteValue(){
            return value->get();
        }

        jshort JByte::shortValue() {
            return (jshort)value->get();
        }

        jint JByte::intValue(){
            return (jint)value->get();
        }

        jlong JByte::longValue(){
            return (jlong)value->get();
        }

        jfloat JByte::floatValue(){
            return (jfloat)value->get();
        }

        jdouble JByte::doubleValue(){
            return (jdouble)value->get();
        }

        void JByte::setPrimitiveByte(JPrimitiveByte* value){
            this->value=value;
        }

        JPrimitiveByte* JByte::getPrimitiveByte(){
            return value;
        }

        jint JByte::compareTo(JObject *o){
            JByte* b=dynamic_cast<JByte*>(o);
            return compare(value->get(),b->get());
        }

        jint JByte::hashCode(){
            return hashCode(value->get());
        }

        JString* JByte::toString(){
            JStringBuilder* builder=new JStringBuilder();
            builder->append(value->get());
            return builder->toString();
        }

        JByte::~JByte(){
        }
    }
}
