#ifndef JCPP_LANG_JCHARACTERDATALATIN1_H
#define JCPP_LANG_JCHARACTERDATALATIN1_H

#include "jcpp/lang/JCharacterData.h"
#include "jcpp/lang/JPrimitiveIntArray.h"
#include "jcpp/lang/JCharacter.h"

namespace jcpp {
	namespace lang {

	// @Class(canonicalName="java.lang.CharacterDataLatin1", simpleName="CharacterDataLatin1");
	class JCPP_EXPORT JCharacterDataLatin1 : public JCharacterData {
	protected:
		static JString* A_DATA;
		static JPrimitiveCharArray* sharpsMap;
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

		virtual jint toUpperCaseEx(jint ch);

		virtual JPrimitiveCharArray* toUpperCaseCharArray(jint ch);

	private:
		JCharacterDataLatin1();

		static JPrimitiveCharArray* initSharpsMap();
		static JPrimitiveIntArray* initA();
		static JString* initA_DATA();
		static JPrimitiveCharArray* initB();

	public:
		static JClass* getClazz();

		static JCharacterDataLatin1* instance;

	};

	}
}

#endif /* JCHARACTERDATALATIN1_H_ */
