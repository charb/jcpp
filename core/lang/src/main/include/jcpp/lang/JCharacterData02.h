#ifndef JCPP_LANG_JCHARACTERDATA02_H
#define JCPP_LANG_JCHARACTERDATA02_H

#include "jcpp/lang/JCharacter.h"
#include "jcpp/lang/JCharacterData.h"
#include "jcpp/lang/JPrimitiveCharArray.h"
#include "jcpp/lang/JPrimitiveIntArray.h"

namespace jcpp {
	namespace lang {

	// @Class(canonicalName="java.lang.CharacterData02", simpleName="CharacterData02");
	class JCPP_EXPORT JCharacterData02 : public JCharacterData {
	public:
		static JCharacterData* instance;

		static JClass* getClazz();

	private:
		JCharacterData02();
		static JPrimitiveIntArray* initA();
		static JPrimitiveCharArray* initX();
		static JPrimitiveCharArray* initY();
		static JString* initA_DATA();
		static JPrimitiveCharArray* initB();

	protected:
		static JString* A_DATA;
		static JPrimitiveCharArray* X;
		static JPrimitiveCharArray* Y;
		static JPrimitiveIntArray* A;
		static JPrimitiveCharArray* B;

		virtual jint getProperties(jint ch);

		jint getPropertiesEx(jint ch);

		virtual jbool isOtherLowercase(jint ch);

		virtual jbool isOtherUppercase(jint ch);

		virtual jbool isOtherAlphabetic(jint ch);

		virtual jbool isIdeographic(jint ch);

		virtual jint getType(jint ch);

		virtual jbool isJavaIdentifierStart(jint ch);

		virtual jbool isJavaIdentifierPart(jint ch);

		virtual jbool isUnicodeIdentifierStart(jint ch);

		virtual jbool isUnicodeIdentifierPart(jint ch);

		virtual jbool isIdentifierIgnorable(jint ch);

		virtual jint toLowerCase(jint ch);

		virtual jint toUpperCase(jint ch);

		virtual jint toTitleCase(jint ch);

		virtual jint digit(jint ch, jint radix);

		virtual jint getNumericValue(jint ch);

		virtual jbool isWhitespace(jint ch);

		virtual jbyte getDirectionality(jint ch);

		virtual jbool isMirrored(jint ch);

	};

	}
}

#endif /* JCHARACTERDATA02_H_ */
