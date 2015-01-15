#ifndef JCPP_LANG_JCHARACTERDATA_H
#define JCPP_LANG_JCHARACTERDATA_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JPrimitiveCharArray.h"


namespace jcpp {
	namespace lang {

	class JCharacterDataLatin1;

	// @Class(canonicalName="java.lang.CharacterData", simpleName="CharacterData");
	class JCPP_EXPORT JCharacterData : public JObject {

	protected:
		JCharacterData(jcpp::lang::JClass* clazz);

	public:
		static JClass* getClazz();

		virtual jint getProperties(jint ch) = 0;
		virtual jint getType(jint ch) = 0;
		virtual jbool isWhitespace(jint ch) = 0;
		virtual jbool isMirrored(jint ch) = 0;
		virtual jbool isJavaIdentifierStart(jint ch) = 0;
		virtual jbool isJavaIdentifierPart(jint ch) = 0;
		virtual jbool isUnicodeIdentifierStart(jint ch) = 0;
		virtual jbool isUnicodeIdentifierPart(jint ch) = 0;
		virtual jbool isIdentifierIgnorable(jint ch) = 0;
		virtual jint toLowerCase(jint ch) = 0;
		virtual jint toUpperCase(jint ch) = 0;
		virtual jint toTitleCase(jint ch) = 0;
		virtual jint digit(jint ch, jint radix) = 0;
		virtual jint getNumericValue(jint ch) = 0;
		virtual jbyte getDirectionality(jint ch) = 0;

		jint toUpperCaseEx(jint ch);

		JPrimitiveCharArray* toUpperCaseCharArray(jint ch);

		jbool isOtherLowercase(jint ch);

		jbool isOtherUppercase(jint ch);

		jbool isOtherAlphabetic(jint ch);

		jbool isIdeographic(jint ch);

		static JCharacterData* of(jint ch);
	};

	}
}

#endif /* JCHARACTERDATA_H_ */
