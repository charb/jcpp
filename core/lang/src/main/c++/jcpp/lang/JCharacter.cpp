#include "jcpp/lang/JCharacter.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/io/JSerializable.h"
#include "jcpp/lang/JStringBuilder.h"
#include "jcpp/lang/reflect/JField.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;
using namespace jcpp::io;

namespace jcpp{
    namespace lang{

        jint JCharacter::hashCode(jchar c){
            return (jint)c;
        }

        jint JCharacter::compare(jchar x,jchar y){
            return x-y;
        }

        jbool JCharacter::isJavaIdentifierPart(jchar c){
            return isJavaIdentifierPart((jint)c);
        }

        jbool JCharacter::isJavaIdentifierPart(jint codePoint) {
        	return (JCharacterData::of(codePoint))->isJavaIdentifierPart(codePoint);
        }

        jbool JCharacter::isSupplementaryCodePoint(jint codePoint) {
        	return codePoint >= MIN_SUPPLEMENTARY_CODE_POINT
        			&& codePoint < MAX_CODE_POINT + 1;
        }

        jbool JCharacter::isHighSurrogate(jchar ch){
        	return ch >= MIN_HIGH_SURROGATE && ch < (MAX_HIGH_SURROGATE + 1);
        }

        jbool JCharacter::isLowSurrogate(jchar ch){
        	return ch >= MIN_LOW_SURROGATE && ch < (MAX_LOW_SURROGATE + 1);
        }

        jbool JCharacter::isSurrogate(jchar ch){
        	return ch >= MIN_SURROGATE && ch < (MAX_SURROGATE + 1);
        }


        jchar JCharacter::toUpperCase(jchar ch){
        	return (jchar)toUpperCase((jint)ch);
        }

        jint JCharacter::toUpperCase(jint codePoint){
        	return JCharacterData::of(codePoint)->toUpperCase(codePoint);
        }

        jchar JCharacter::toLowerCase(jchar ch){
        	return (jchar)toLowerCase((jint)ch);
        }

        jint JCharacter::toLowerCase(jint codePoint) {
        	return JCharacterData::of(codePoint)->toLowerCase(codePoint);
        }

        jbool JCharacter::isWhitespace(jchar c){
        	return isWhitespace((jint)c);
        }

        jbool JCharacter::isWhitespace(jint codePoint) {
        	return JCharacterData::of(codePoint)->isWhitespace(codePoint);
        }

        jint JCharacter::toCodePoint(jchar high, jchar low) {
        	return ((high<<10) + low) + (MIN_SUPPLEMENTARY_CODE_POINT
        								 -	(MIN_HIGH_SURROGATE << 10)
        								 -	MIN_LOW_SURROGATE);
        }

        jint JCharacter::getType(jchar c) {
        	return JCharacter::getType((jint)c);
        }

        jint JCharacter::getType(jint codePoint) {
        	return JCharacterData::of(codePoint)->getType(codePoint);
        }

        jbool JCharacter::isDigit(jchar c) {
        	return JCharacter::isDigit((jint)c);
        }

        jbool JCharacter::isDigit(jint codePoint) {
        	return ( JCharacter::getType(codePoint) == JCharacter::DECIMAL_DIGIT_NUMBER );
        }

        jchar JCharacter::highSurrogate(jint codePoint){
        	return (jchar)(((unsigned int)codePoint >> 10)
        			+ (MIN_HIGH_SURROGATE - ((unsigned int)MIN_SUPPLEMENTARY_CODE_POINT >> 10)));
        }

        jchar JCharacter::lowSurrogate(jint codePoint){
        	return (jchar)((codePoint & 0x3ff) + MIN_LOW_SURROGATE);
        }

        jint JCharacter::charCount(jint codePoint){
            return codePoint >= MIN_SUPPLEMENTARY_CODE_POINT ? 2 : 1;
        }

        jchar JCharacter::MIN_VALUE = JCHAR_MIN;

        jchar JCharacter::MAX_VALUE = JCHAR_MAX;

        jcpp::lang::JClass* JCharacter::TYPE = JPrimitiveChar::getClazz();

        JCharacter::JCharacter(char value):JObject(getClazz()){
            this->value=new JPrimitiveChar(value);
        }

        JCharacter::JCharacter(jchar value):JObject(getClazz()){
            this->value=new JPrimitiveChar(value);
        }

        JCharacter::JCharacter():JObject(getClazz()){
            this->value=new JPrimitiveChar((jchar)0);
        }

        jbool JCharacter::equals(JObject* other){
            if ((other != null) && other->getClass()==getClazz()){
                JCharacter* s=dynamic_cast<JCharacter*>(other);
                return value->equals(s->value);
            }
            return false;
        }

        void JCharacter::set(jchar value){
            this->value->set(value);
        }

        jchar JCharacter::get(){
            return value->get();
        }

        jchar JCharacter::charValue(){
            return value->get();
        }

        void JCharacter::setPrimitiveChar(JPrimitiveChar* value){
            this->value=value;
        }

        JPrimitiveChar* JCharacter::getPrimitiveChar(){
            return value;
        }

        jint JCharacter::compareTo(JObject *o){
            JCharacter* c=dynamic_cast<JCharacter*>(o);
            return compare(value->get(),c->value->get());
        }

        jint JCharacter::hashCode(){
            return hashCode(value->get());
        }

        JString* JCharacter::toString(){
            JStringBuilder* builder=new JStringBuilder();
            builder->append(value->get());
            return builder->toString();
        }

        JCharacter::~JCharacter(){
        }
    }
}
