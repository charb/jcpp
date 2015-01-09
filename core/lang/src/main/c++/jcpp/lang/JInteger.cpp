#include "jcpp/lang/JInteger.h"
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
        class JIntegerClass : public jcpp::lang::JClass{
        protected:
            static JObject* createJInteger(jcpp::util::JList* args){
                return new JInteger();
            }

            static JObject* staticGetValue(JObject* object){
                JInteger* b=(JInteger*)object;
                return b->getPrimitiveInt();
            }

            static void staticSetValue(JObject* obj,JObject* value){
                JInteger* b=(JInteger*)obj;
                b->setPrimitiveInt((JPrimitiveInt*)value);
            }

            static JObject** adrValue(JObject* obj){
                JInteger* b=(JInteger*)obj;
                return (JObject**)(&b->value);
            }

        public:
            JIntegerClass():jcpp::lang::JClass(){
                this->canonicalName=new JString("java.lang.Integer");
                this->name=new JString("java.lang.Integer");
                this->simpleName=new JString("Integer");
                this->serialVersionUID=1360826667806852920ULL;
            }

            virtual void initialize(){
                addInterface(JSerializable::getClazz());
                addInterface(JComparable::getClazz());

                addConstructor(new JConstructor(JInteger::getClazz(),JModifier::PUBLIC,createJInteger));

                addField(new JField(new JString("value"),JPrimitiveInt::getClazz(),this,staticGetValue,staticSetValue,adrValue));
            }

            virtual jcpp::lang::JClass* getSuperclass(){
                return JNumber::getClazz();
            }
        };

        static jcpp::lang::JClass* clazz;

        jcpp::lang::JClass* JInteger::getClazz(){
            if (clazz==null){
                clazz=new JIntegerClass();
            }
            return clazz;
        }

        jint JInteger::hashCode(jint i){
            return i;
        }

        jint JInteger::compare(jint x,jint y){
            return x-y;
        }

        JInteger* JInteger::valueOf(JString* s){
        	return new JInteger(s->getNativeString().toJint());
        }

        JString* JInteger::toString(jint d){
        	return new JString(NativeString::valueOf(d));
        }

        jint JInteger::MIN_VALUE = JINT_MIN;

        jint JInteger::MAX_VALUE = JINT_MAX;

        jint JInteger::SIZE = 32;

        jint JInteger::BYTES = SIZE / JByte::SIZE;

        jcpp::lang::JClass* JInteger::TYPE = JPrimitiveInt::getClazz();

		// All possible chars for representing a number as a String
		jchar digits [36] = {
			'0' , '1' , '2' , '3' , '4' , '5' ,
			'6' , '7' , '8' , '9' , 'a' , 'b' ,
			'c' , 'd' , 'e' , 'f' , 'g' , 'h' ,
			'i' , 'j' , 'k' , 'l' , 'm' , 'n' ,
			'o' , 'p' , 'q' , 'r' , 's' , 't' ,
			'u' , 'v' , 'w' , 'x' , 'y' , 'z'
		};

		JString* JInteger::toUnsignedString(jint i, jint shift) {
			unsigned int ui = (unsigned int) i;
			JPrimitiveCharArray* buf = new JPrimitiveCharArray(32);
			int charPos = 32;
			int radix = 1 << shift;
			int mask = radix - 1;
			do {
				buf->setChar(--charPos, digits[ui & mask]);
				ui >>= shift;
			} while (ui != 0);

			return new JString(buf, charPos, (32 - charPos));
		}

        JString* JInteger::toHexString(jint i) {
        	return toUnsignedString(i, 4);
        }

        JString* JInteger::toOctalString(jint i) {
        	return toUnsignedString(i, 3);
        }

        JString* JInteger::toBinaryString(jint i) {
        	return toUnsignedString(i, 1);
        }

        JInteger::JInteger(jint value):JNumber(getClazz()){
            this->value=new JPrimitiveInt(value);
        }

        JInteger::JInteger():JNumber(getClazz()){
            this->value=new JPrimitiveInt(0);
        }

        jbool JInteger::equals(JObject* other){
            if ((other != null) && other->getClass()==getClazz()){
                JInteger* s=dynamic_cast<JInteger*>(other);
                return value->equals(s->value);
            }
            return false;
        }

        void JInteger::set(jint value){
            this->value->set(value);
        }

        jint JInteger::get(){
            return value->get();
        }

        jbyte JInteger::byteValue(){
            return (jbyte)value->get();
        }

        jshort JInteger::shortValue(){
            return (jshort)value->get();
        }

        jint JInteger::intValue(){
            return value->get();
        }

        jlong JInteger::longValue(){
            return (jlong)value->get();
        }

        jfloat JInteger::floatValue(){
            return (jfloat)value->get();
        }

        jdouble JInteger::doubleValue(){
            return (jdouble)value->get();
        }

        void JInteger::setPrimitiveInt(JPrimitiveInt* value){
            this->value=value;
        }

        JPrimitiveInt* JInteger::getPrimitiveInt(){
            return value;
        }

        jint JInteger::compareTo(JObject *o){
            JInteger* i=dynamic_cast<JInteger*>(o);
            return compare(get(),i->get());
        }

        jint JInteger::hashCode(){
            return hashCode(value->get());
        }

        JString* JInteger::toString(){
            JStringBuilder* builder=new JStringBuilder();
            builder->append(value->get());
            return builder->toString();
        }

        JInteger::~JInteger(){
        }
    }
}
