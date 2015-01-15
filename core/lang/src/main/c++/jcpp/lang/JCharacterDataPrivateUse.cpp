#include "jcpp/lang/JCharacterDataPrivateUse.h"

namespace jcpp {
	namespace lang {

	jint JCharacterDataPrivateUse::getProperties(jint ch) {
		return 0;
	}

	jint JCharacterDataPrivateUse::getType(jint ch) {
		return (ch & 0xFFFE) == 0xFFFE?
				JCharacter::UNASSIGNED
				: JCharacter::PRIVATE_USE;
	}

	jbool JCharacterDataPrivateUse::isJavaIdentifierStart(jint ch) {
		return false;
	}

	jbool JCharacterDataPrivateUse::isJavaIdentifierPart(jint ch) {
		return false;
	}

	jbool JCharacterDataPrivateUse::isUnicodeIdentifierStart(jint ch) {
		return false;
	}

	jbool JCharacterDataPrivateUse::isUnicodeIdentifierPart(jint ch) {
		return false;
	}

	jbool JCharacterDataPrivateUse::isIdentifierIgnorable(jint ch) {
		return false;
	}

	jint JCharacterDataPrivateUse::toLowerCase(jint ch) {
		return ch;
	}

	jint JCharacterDataPrivateUse::toUpperCase(jint ch) {
		return ch;
	}

	jint JCharacterDataPrivateUse::toTitleCase(jint ch) {
		return ch;
	}

	jint JCharacterDataPrivateUse::digit(jint ch, jint radix) {
		return -1;
	}

	jint JCharacterDataPrivateUse::getNumericValue(jint ch) {
		return -1;
	}

	jbool JCharacterDataPrivateUse::isWhitespace(jint ch) {
		return false;
	}

	jbyte JCharacterDataPrivateUse::getDirectionality(jint ch) {
		return (ch & 0xFFFE) == 0xFFFE ?
				JCharacter::DIRECTIONALITY_UNDEFINED
				: JCharacter::DIRECTIONALITY_LEFT_TO_RIGHT;
	}

	jbool JCharacterDataPrivateUse::isMirrored(jint ch) {
		return false;
	}

	JCharacterData* JCharacterDataPrivateUse::instance = new JCharacterDataPrivateUse();

	JCharacterDataPrivateUse::JCharacterDataPrivateUse() : JCharacterData(getClazz()) {
	}

	}
}
