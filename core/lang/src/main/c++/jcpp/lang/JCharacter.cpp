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
        class JCharacterClass : public jcpp::lang::JClass{
        protected:
            static JObject* createJCharacter(jcpp::util::JList* args){
                return new JCharacter();
            }

            static JObject* staticGetValue(JObject* object){
                JCharacter* b=(JCharacter*)object;
                return b->getPrimitiveChar();
            }

            static void staticSetValue(JObject* obj,JObject* value){
                JCharacter* b=(JCharacter*)obj;
                b->setPrimitiveChar((JPrimitiveChar*)value);
            }

            static JObject** adrValue(JObject* obj){
                JCharacter* b=(JCharacter*)obj;
                return (JObject**)(&b->value);
            }

        public:
            JCharacterClass():jcpp::lang::JClass(){
                this->canonicalName=new JString("java.lang.Character");
                this->name=new JString("java.lang.Character");
                this->simpleName=new JString("Character");
                this->serialVersionUID=3786198910865385080ULL;
            }

            virtual void initialize(){
                addInterface(JSerializable::getClazz());
                addInterface(JComparable::getClazz());

                JConstructor* cons=addConstructor(new JConstructor(JCharacter::getClazz(),JModifier::PUBLIC,createJCharacter));

                addField(new JField(new JString("value"),JPrimitiveChar::getClazz(),this,staticGetValue,staticSetValue,adrValue));
            }

            virtual jcpp::lang::JClass* getSuperclass(){
                return JObject::getClazz();
            }
        };

        static jcpp::lang::JClass* clazz;

        jcpp::lang::JClass* JCharacter::getClazz(){
            if (clazz==null){
                clazz=new JCharacterClass();
            }
            return clazz;
        }

        jint JCharacter::hashCode(jchar c){
            return (jint)c;
        }

        jint JCharacter::compare(jchar x,jchar y){
            return x-y;
        }

        jbool JCharacter::isJavaIdentifierPart(jchar c){
            return false;//TODO!!!!!!!!!!!!!!!
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

        // TODO update with CharacterData
        jchar JCharacter::toUpperCase(jchar ch){
        	return (97 <= ch) && (ch <= 122) ? ch - 32 : ch;
        }

        // TODO update with CharacterData
        jchar JCharacter::toLowerCase(jchar ch){
        	return (65 <= ch) && (ch <= 90) ? ch + 32 : ch;
        }

        // TODO update with CharacterData
        jbool JCharacter::isWhitespace(jchar c){
            return c == 0x00A0 || c == 0x2007 || c == 0x202F || c == 0x0009 || c == 0x000A || c == 0x000B || c == 0x000C || c == 0x000D || c == 0x001C || c == 0x001D || c == 0x001E || c == 0x001F;
        }

        jint JCharacter::toCodePoint(jchar high, jchar low) {
        	return ((high<<10) + low) + (MIN_SUPPLEMENTARY_CODE_POINT
        								 -	(MIN_HIGH_SURROGATE << 10)
        								 -	MIN_LOW_SURROGATE);
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
