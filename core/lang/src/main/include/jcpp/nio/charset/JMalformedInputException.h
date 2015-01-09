#ifndef JCPP_NIO_CHARSET_JMALFORMEDINPUTEXCEPTION_H
#define JCPP_NIO_CHARSET_JMALFORMEDINPUTEXCEPTION_H

#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/nio/charset/JCharacterCodingException.h"
#include "jcpp/lang/JStringBuilder.h"

namespace jcpp {
	namespace nio {
		namespace charset {

	// @Class(canonicalName="java.nio.charset.MalformedInputException", simpleName="MalformedInputException");
	class JCPP_EXPORT JMalformedInputException : public JCharacterCodingException {
	private:
		JPrimitiveInt* inputLength;

	public:
		static jcpp::lang::JClass* getClazz();

		JMalformedInputException();
		JMalformedInputException(JPrimitiveInt* inputLength);
		JPrimitiveInt* getInputLength();

		virtual ~JMalformedInputException();

		friend class JMalformedInputExceptionClass;
	};


		}
	}
}


#endif /* JMALFORMEDINPUTEXCEPTION_H_ */
