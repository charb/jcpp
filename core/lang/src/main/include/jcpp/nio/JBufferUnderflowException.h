#ifndef JCPP_NIO_JBUFFERUNDERFLOWEXCEPTION_H
#define JCPP_NIO_JBUFFERUNDERFLOWEXCEPTION_H

#include "jcpp/lang/JException.h"
#include "jcpp/lang/JRuntimeException.h"
#include "jcpp/lang/reflect/JModifier.h"

namespace jcpp {
	namespace nio {

	// @Class(canonicalName="java.nio.BufferUnderflowException", simpleName="BufferUnderflowException");
	class JCPP_EXPORT JBufferUnderflowException : public JRuntimeException {
	private:
		static const jlong serialVersionUID = -1713313658691622206LL;

	public:

		JBufferUnderflowException();

		virtual ~JBufferUnderflowException();

		static jcpp::lang::JClass* getClazz();

	};

	}
}



#endif /* JBUFFERUNDERFLOWEXCEPTION_H_ */
