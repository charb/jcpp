#include "jcpp/lang/JDouble.h"
#include "jcpp/lang/JNumber.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/io/JSerializable.h"
#include "jcpp/lang/JByte.h"
#include "jcpp/lang/JStringBuilder.h"
#include "jcpp/lang/reflect/JField.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/JIllegalArgumentException.h"

using namespace jcpp::lang::reflect;
using namespace jcpp::io;

namespace jcpp{
    namespace lang{

        jint JDouble::hashCode(jdouble d){
            return (jint)d;
        }

        jint JDouble::compare(jdouble d1,jdouble d2){
            return d1-d2;
        }

        JDouble* JDouble::valueOf(JString* s){
            return new JDouble(s->getNativeString().toJdouble());
        }

        JString* JDouble::toString(jdouble d){
            return new JString(NativeString::valueOf(d));
        }

        jdouble JDouble::parseDouble(JString* s){
        	if(s == null) {
        		throw new JIllegalArgumentException(new JString("Invalid null string to parse to double"));
        	}
            return s->getNativeString().toJdouble();
        }                

        jdouble JDouble::MIN_VALUE = JDOUBLE_MIN_POSITIVE;

        jdouble JDouble::MAX_VALUE = JDOUBLE_MAX; 

        jint JDouble::SIZE = 64;

        jint JDouble::BYTES = SIZE / JByte::SIZE;

        jcpp::lang::JClass* JDouble::TYPE = JPrimitiveDouble::getClazz();

        JDouble::JDouble(jdouble value):JNumber(JDouble::getClazz()){
            this->value=new JPrimitiveDouble(value);
        }

        JDouble::JDouble():JNumber(JDouble::getClazz()){
            this->value=new JPrimitiveDouble(0);
        }

        jbool JDouble::equals(JObject* other){
            if ((other != null) && other->getClass()==getClazz()){
                JDouble* s=dynamic_cast<JDouble*>(other);
                return value->equals(s->value);
            }
            return false;
        }

        void JDouble::set(jdouble value){
            this->value->set(value);
        }

        jdouble JDouble::get(){
            return value->get();
        }

        jbyte JDouble::byteValue(){
            return (jbyte)value->get();
        }

        jshort JDouble::shortValue(){
            return (jshort)value->get();
        }

        jint JDouble::intValue(){
            return (jint)value->get();
        }

        jlong JDouble::longValue(){
            return (jlong)value->get();
        }

        jfloat JDouble::floatValue(){
            return (jfloat)value->get();
        }

        jdouble JDouble::doubleValue(){
            return value->get();
        }

        void JDouble::setPrimitiveDouble(JPrimitiveDouble* value){
            this->value=value;
        }

        JPrimitiveDouble* JDouble::getPrimitiveDouble(){
            return value;
        }

        jint JDouble::compareTo(JObject *o){
            JDouble* d=dynamic_cast<JDouble*>(o);
            return compare(value->get(),d->get());
        }

        jint JDouble::hashCode(){
            return hashCode(value->get());
        }

        JString* JDouble::toString(){
            JStringBuilder* builder=new JStringBuilder();
            builder->append(value->get());
            return builder->toString();
        }

        JDouble::~JDouble(){
        }
    }
}
