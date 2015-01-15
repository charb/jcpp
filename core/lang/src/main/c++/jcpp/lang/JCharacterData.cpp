#include "jcpp/lang/JCharacterData.h"
#include "jcpp/lang/JCharacterDataLatin1.h"
#include "jcpp/lang/JCharacterData00.h"
#include "jcpp/lang/JCharacterData01.h"
#include "jcpp/lang/JCharacterData02.h"
#include "jcpp/lang/JCharacterData0E.h"
#include "jcpp/lang/JCharacterDataPrivateUse.h"
#include "jcpp/lang/JCharacterDataUndefined.h"

namespace jcpp {
	namespace lang {

		JCharacterData::JCharacterData(jcpp::lang::JClass* clazz) : JObject(clazz) {
		}

		jint JCharacterData::toUpperCaseEx(jint ch) {
			return toUpperCase(ch);
		}

		JPrimitiveCharArray* JCharacterData::toUpperCaseCharArray(jint ch) {
			return null;
		}

		jbool JCharacterData::isOtherLowercase(jint ch) {
			return false;
		}

		jbool JCharacterData::isOtherUppercase(jint ch) {
			return false;
		}

		jbool JCharacterData::isOtherAlphabetic(jint ch) {
			return false;
		}

		jbool JCharacterData::isIdeographic(jint ch) {
			return false;
		}

		JCharacterData* JCharacterData::of(jint ch) {
			if (ch >> 8 == 0) {
				return JCharacterDataLatin1::instance;
			} else {
				switch (ch >> 16) {
				case 0:
					return JCharacterData00::instance;
				case 1:
					return JCharacterData01::instance;
				case 2:
					return JCharacterData02::instance;
				case 14:
					return JCharacterData0E::instance;
				case 15:
				case 16:
					return JCharacterDataPrivateUse::instance;
				default:
					return JCharacterDataUndefined::instance;
				}
			}
		}

	}
}
