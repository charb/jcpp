#ifndef JCPP_LANG_JCHARACTERDATAPRIVATEUSE_H
#define JCPP_LANG_JCHARACTERDATAPRIVATEUSE_H

#include "jcpp/lang/JCharacter.h"
#include "jcpp/lang/JCharacterData.h"

namespace jcpp {
	namespace lang {

	// @Class(canonicalName="java.lang.CharacterDataPrivateUse", simpleName="CharacterDataPrivateUse");
	class JCPP_EXPORT JCharacterDataPrivateUse : public JCharacterData {
	public:
		static JCharacterData* instance;

		static JClass* getClazz();

	private:
		JCharacterDataPrivateUse();

	protected:
		jint getProperties(jint ch);

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



#endif /* JCHARACTERDATAPRIVATEUSE_H_ */
