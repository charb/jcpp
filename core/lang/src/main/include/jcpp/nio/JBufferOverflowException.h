#ifndef JCPP_NIO_JBUFFEROVERFLOWEXCEPTION_H
#define JCPP_NIO_JBUFFEROVERFLOWEXCEPTION_H

#include "jcpp/lang/JException.h"
#include "jcpp/lang/JRuntimeException.h"
#include "jcpp/lang/reflect/JModifier.h"

namespace jcpp {
	namespace nio {

	// @Class(canonicalName="java.nio.BufferOverflowException", simpleName="BufferOverflowException");
	class JCPP_EXPORT JBufferOverflowException : public JRuntimeException {
	private:
		static const jlong serialVersionUID = -5484897634319144535LL;

	public:

		JBufferOverflowException();

		virtual ~JBufferOverflowException();

		static jcpp::lang::JClass* getClazz();
	};

	}
}



#endif /* JBUFFEROVERFLOWEXCEPTION_H_ */
