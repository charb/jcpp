#ifndef JCPP_LANG_JCHARACTER_H
#define JCPP_LANG_JCHARACTER_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JPrimitiveChar.h"
#include "jcpp/lang/JComparable.h"
#include "jcpp/io/JSerializable.h"
#include "jcpp/lang/JCharacterData.h"

using namespace jcpp::io;

namespace jcpp{
    namespace lang{
    	class JCharacterClass;

    	// @Class(canonicalName="java.lang.Character", simpleName="Character");
        class JCPP_EXPORT JCharacter : public JObject, public JComparable, public JSerializable{
        	private:
        		static const jlong serialVersionUID = 3786198910865385080LL;

        	public:
    			static const jchar MIN_HIGH_SURROGATE = 0xD800;
    			static const jchar MAX_HIGH_SURROGATE = 0xDBFF;
    			static const jchar MIN_LOW_SURROGATE = 0xDC00;
    			static const jchar MAX_LOW_SURROGATE = 0xDFFF;
    			static const jchar MIN_SURROGATE = MIN_HIGH_SURROGATE;
    			static const jchar MAX_SURROGATE = MAX_LOW_SURROGATE;
    			static const jint MIN_SUPPLEMENTARY_CODE_POINT = 0x010000;
    			static const jint MIN_CODE_POINT = 0x000000;
    			static const jint MAX_CODE_POINT = 0x10FFFF;
    			static const jint MIN_RADIX = 2;
    			static const jint MAX_RADIX = 36;
    			static const jbyte DECIMAL_DIGIT_NUMBER = 9;
    			static const jint ERROR = 0xFFFFFFFF;
    			static const jbyte DIRECTIONALITY_LEFT_TO_RIGHT = 1;
    			static const jbyte DIRECTIONALITY_LEFT_TO_RIGHT_EMBEDDING = 14;
    			static const jbyte DIRECTIONALITY_RIGHT_TO_LEFT_EMBEDDING = 16;
    			static const jbyte DIRECTIONALITY_POP_DIRECTIONAL_FORMAT = 18;
    			static const jbyte DIRECTIONALITY_LEFT_TO_RIGHT_OVERRIDE = 15;
    			static const jbyte DIRECTIONALITY_RIGHT_TO_LEFT_OVERRIDE = 17;
    			static const jbyte DIRECTIONALITY_UNDEFINED = -1;
    			static const jbyte UNASSIGNED = 0;
    			static const jbyte PRIVATE_USE = 18;
    			static const jbyte UPPERCASE_LETTER = 1;
    			static const jbyte LOWERCASE_LETTER = 2;
    			static const jbyte TITLECASE_LETTER = 3;
    			static const jbyte MODIFIER_LETTER = 4;
    			static const jbyte OTHER_LETTER = 5;
    			static const jbyte NON_SPACING_MARK = 6;
    			static const jbyte ENCLOSING_MARK = 7;
    			static const jbyte COMBINING_SPACING_MARK = 8;
    			static const jbyte LETTER_NUMBER = 10;



            protected:
                JPrimitiveChar* value;
                void setPrimitiveChar(JPrimitiveChar* value);
                JPrimitiveChar* getPrimitiveChar();
                friend class JCharacterClass;

            public:
                JCharacter();

                JCharacter(char value);

                JCharacter(jchar value);

                static jcpp::lang::JClass* getClazz();

                static jint hashCode(jchar c);

                static jint compare(jchar x,jchar y);

                static jbool isJavaIdentifierPart(jchar c);

                static jbool isJavaIdentifierPart(jint codePoint);

                static jbool isSupplementaryCodePoint(jint codePoint);

                static jbool isHighSurrogate(jchar ch);

                static jbool isLowSurrogate(jchar ch);

                static jbool isSurrogate(jchar ch);

                static jchar toUpperCase(jchar ch);

                static jint toUpperCase(jint codePoint);

                static jchar toLowerCase(jchar ch);

                static jint toLowerCase(jint codePoint);

                static jbool isWhitespace(jchar c);

                static jbool isWhitespace(jint codePoint);

                static jint getType(jchar c);

                static jint getType(jint codePoint);

                static jbool isDigit(jchar c);

                static jbool isDigit(jint codePoint);

                static jint toCodePoint(jchar high, jchar low);

                static jchar highSurrogate(jint codePoint);

                static jchar lowSurrogate(jint codePoint);

                static jint charCount(jint codePoint);

                static jchar MIN_VALUE;

                static jchar MAX_VALUE;

                static jcpp::lang::JClass* TYPE;

                virtual void set(jchar value);

                virtual jchar get();

                virtual jchar charValue();

                virtual jint compareTo(JObject * o);

                virtual jbool equals(JObject* other);

                virtual jint hashCode();

                virtual JString* toString();

                virtual ~JCharacter();
        };
    }
}
#endif
