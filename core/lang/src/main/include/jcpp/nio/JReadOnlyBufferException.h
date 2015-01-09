#ifndef JCPP_NIO_JREADONLYBUFFEREXCEPTION_H
#define JCPP_NIO_JREADONLYBUFFEREXCEPTION_H

#include "jcpp/native/api/NativeInclude.h"
#include "jcpp/lang/JUnsupportedOperationException.h"
#include "jcpp/lang/reflect/JModifier.h"

namespace jcpp {
	namespace nio {

	// @Class(canonicalName="java.nio.ReadOnlyBufferException", simpleName="ReadOnlyBufferException");
	class JCPP_EXPORT JReadOnlyBufferException : public JUnsupportedOperationException{
	private:
		static const jlong serialVersionUID = -1210063976496234090LL;

	public:
		JReadOnlyBufferException();

		static jcpp::lang::JClass* getClazz();

		virtual ~JReadOnlyBufferException();
	};

	}
}



#endif /* JREADONLYBUFFEREXCEPTION_H_ */
