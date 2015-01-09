#ifndef JCPP_NIO_CS_JSURROGATE_H
#define JCPP_NIO_CS_JSURROGATE_H

#include "jcpp/lang/JCharacter.h"
#include "jcpp/nio/charset/JCoderResult.h"
#include "jcpp/nio/JCharBuffer.h"
#include <cassert>

using namespace jcpp::nio::charset;

namespace jcpp {
	namespace nio {
		namespace cs {


	// @Class(canonicalName="sun.nio.cs.Surrogate", simpleName="Surrogate");
	class JCPP_EXPORT JSurrogate : public JObject {
	public:
		static const jchar MIN_HIGH = JCharacter::MIN_HIGH_SURROGATE;
		static const jchar MAX_HIGH = JCharacter::MAX_HIGH_SURROGATE;
		static const jchar MIN_LOW = JCharacter::MIN_LOW_SURROGATE;
		static const jchar MAX_LOW = JCharacter::MAX_LOW_SURROGATE;
		static const jchar MIN = JCharacter::MIN_SURROGATE;
		static const jchar MAX = JCharacter::MAX_SURROGATE;
		static const jchar UCS4_MIN = JCharacter::MIN_SUPPLEMENTARY_CODE_POINT;
		static const jchar UCS4_MAX = JCharacter::MAX_CODE_POINT;

		// @Class(canonicalName="sun.nio.cs.Surrogate.Parser", simpleName="Parser");
		class JCPP_EXPORT JParser : public JObject {
		private:
			jint character;
			JCoderResult* _error;
			jbool isPair;

		public:
			JParser();

			static jcpp::lang::JClass* getClazz();

			JCoderResult* error();

			jint parse(jchar c, JCharBuffer* in);

			jint parse(jchar c, JPrimitiveCharArray* ia, jint ip, jint il);

			virtual ~JParser();
		};

	public:
		JSurrogate();

		static jcpp::lang::JClass* getClazz();

		virtual ~JSurrogate();

	};

		}
	}
}


#endif /* JSURROGATE_H_ */
