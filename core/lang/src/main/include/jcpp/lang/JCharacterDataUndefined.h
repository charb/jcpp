#ifndef JCPP_LANG_JCHARACTERDATAUNDEFINED_H
#define JCPP_LANG_JCHARACTERDATAUNDEFINED_H

#include "jcpp/lang/JCharacter.h"
#include "jcpp/lang/JCharacterData.h"

namespace jcpp {
	namespace lang {

	// @Class(canonicalName="java.lang.CharacterDataUndefined", simpleName="CharacterDataUndefined");
	class JCPP_EXPORT JCharacterDataUndefined : public JCharacterData {
	public:
		static JCharacterData* instance;

		static JClass* getClazz();

	private:
		JCharacterDataUndefined();

	protected:
		jint getProperties(jint ch);

		jint getType(jint ch);

		jbool isJavaIdentifierStart(jint ch);

		jbool isJavaIdentifierPart(jint ch);

		jbool isUnicodeIdentifierStart(jint ch);

		jbool isUnicodeIdentifierPart(jint ch);

		jbool isIdentifierIgnorable(jint ch);

		jint toLowerCase(jint ch);

		jint toUpperCase(jint ch);

		jint toTitleCase(jint ch);

		jint digit(jint ch, jint radix);

		jint getNumericValue(jint ch);

		jbool isWhitespace(jint ch);

		jbyte getDirectionality(jint ch);

		jbool isMirrored(jint ch);
	};

	}
}

#endif /* JCHARACTERDATAUNDEFINED_H_ */
