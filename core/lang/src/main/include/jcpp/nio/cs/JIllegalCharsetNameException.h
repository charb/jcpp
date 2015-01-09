#ifndef JCPP_NIO_CS_JILLEGALCHARSETNAMEEXCEPTION_H
#define JCPP_NIO_CS_JILLEGALCHARSETNAMEEXCEPTION_H

#include "jcpp/lang/JIllegalArgumentException.h"
#include "jcpp/lang/reflect/JModifier.h"

namespace jcpp {
	namespace nio {
		namespace cs {

	// @Class(canonicalName="java.nio.charset.IllegalCharsetNameException", simpleName="IllegalCharsetNameException");
	class JCPP_EXPORT JIllegalCharsetNameException : public JIllegalArgumentException {

		private:
		JString* charsetName;

		public:
		JIllegalCharsetNameException();
		JIllegalCharsetNameException(JString* charsetName);

		static jcpp::lang::JClass* getClazz();

		JString* getCharsetName();

		virtual ~JIllegalCharsetNameException();

		friend class JIllegalCharsetNameExceptionClass;
	};

		}
	}
}

#endif /* JILLEGALCHARSETNAMEEXCEPTION_H_ */
