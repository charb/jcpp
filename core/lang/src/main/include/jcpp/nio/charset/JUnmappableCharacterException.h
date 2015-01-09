#ifndef JCPP_NIO_CHARSET_JUNMAPPABLECHARACTEREXCEPTION_H
#define JCPP_NIO_CHARSET_JUNMAPPABLECHARACTEREXCEPTION_H

#include "jcpp/nio/charset/JCharacterCodingException.h"
#include "jcpp/lang/JStringBuilder.h"

namespace jcpp {
	namespace nio {
		namespace charset {

	// @Class(canonicalName="java.nio.charset.UnmappableCharacterException", simpleName="UnmappableCharacterException");
	class JCPP_EXPORT JUnmappableCharacterException : public JCharacterCodingException {
	private:
		static const jlong serialVersionUID = -7026962371537706123LL;

		JPrimitiveInt* inputLength;

	public:
		static jcpp::lang::JClass* getClazz();

		JUnmappableCharacterException();
		JUnmappableCharacterException(JPrimitiveInt* inputLength);
		JPrimitiveInt* getInputLength();

		virtual ~JUnmappableCharacterException();

		friend class JUnmappableCharacterExceptionClass;
	};

		}
	}
}



#endif /* JUNMAPPABLECHARACTEREXCEPTION_H_ */
