#include "jcpp/lang/JCharacterDataUndefined.h"

namespace jcpp {
	namespace lang {

	jint JCharacterDataUndefined::getProperties(jint ch) {
		return 0;
	}

	jint JCharacterDataUndefined::getType(jint ch) {
		return JCharacter::UNASSIGNED;
	}

	jbool JCharacterDataUndefined::isJavaIdentifierStart(jint ch) {
		return false;
	}

	jbool JCharacterDataUndefined::isJavaIdentifierPart(jint ch) {
		return false;
	}

	jbool JCharacterDataUndefined::isUnicodeIdentifierStart(jint ch) {
		return false;
	}

	jbool JCharacterDataUndefined::isUnicodeIdentifierPart(jint ch) {
		return false;
	}

	jbool JCharacterDataUndefined::isIdentifierIgnorable(jint ch) {
		return false;
	}

	jint JCharacterDataUndefined::toLowerCase(jint ch) {
		return ch;
	}

	jint JCharacterDataUndefined::toUpperCase(jint ch) {
		return ch;
	}

	jint JCharacterDataUndefined::toTitleCase(jint ch) {
		return ch;
	}

	jint JCharacterDataUndefined::digit(jint ch, jint radix) {
		return -1;
	}

	jint JCharacterDataUndefined::getNumericValue(jint ch) {
		return -1;
	}

	jbool JCharacterDataUndefined::isWhitespace(jint ch) {
		return false;
	}

	jbyte JCharacterDataUndefined::getDirectionality(jint ch) {
		return JCharacter::DIRECTIONALITY_UNDEFINED;
	}

	jbool JCharacterDataUndefined::isMirrored(jint ch) {
		return false;
	}

	JCharacterData* JCharacterDataUndefined::instance = new JCharacterDataUndefined();

	JCharacterDataUndefined::JCharacterDataUndefined() :JCharacterData(getClazz()) {
	}

	}
}

