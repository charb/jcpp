#ifndef JCPP_LANG_JCHARACTER_H
#define JCPP_LANG_JCHARACTER_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JPrimitiveChar.h"
#include "jcpp/lang/JComparable.h"
#include "jcpp/io/JSerializable.h"

using namespace jcpp::io;

namespace jcpp{
    namespace lang{
    	class JCharacterClass;

        class JCPP_EXPORT JCharacter : public JObject, public JComparable, public JSerializable{
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

                static jbool isSupplementaryCodePoint(jint codePoint);

                static jbool isHighSurrogate(jchar ch);

                static jbool isLowSurrogate(jchar ch);

                static jbool isSurrogate(jchar ch);

                static jchar toUpperCase(jchar ch);

                static jchar toLowerCase(jchar ch);

                static jbool isWhitespace(jchar c);

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
