#ifndef JCPP_NIO_JINVALIDMARKEXCEPTION_H
#define JCPP_NIO_JINVALIDMARKEXCEPTION_H

#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/JIllegalStateException.h"

namespace jcpp {
	namespace nio {

	// @Class(canonicalName="java.nio.InvalidMarkException", simpleName="InvalidMarkException");
	class JCPP_EXPORT JInvalidMarkException : public JIllegalStateException {
	private:
		static const jlong serialVersionUID = 1698329710438510774LL;

	public:

		JInvalidMarkException();

		static jcpp::lang::JClass* getClazz();

		virtual ~JInvalidMarkException();
	};

	}
}



#endif /* JINVALIDMARKEXCEPTION_H_ */
