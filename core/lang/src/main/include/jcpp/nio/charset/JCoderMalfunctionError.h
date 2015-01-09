#ifndef JCPP_NIO_CHARSET_JCODERMALFUNCTIONERROR_H
#define JCPP_NIO_CHARSET_JCODERMALFUNCTIONERROR_H

#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/native/api/NativeInclude.h"
#include "jcpp/lang/JError.h"
#include "jcpp/lang/JException.h"

namespace jcpp {
	namespace nio {
		namespace charset {

	// @Class(canonicalName="java.nio.charset.CoderMalfunctionError", simpleName="CoderMalfunctionError");
	class JCPP_EXPORT JCoderMalfunctionError : public JError {
	private:
		static const jlong serialVersionUID = -1151412348057794301LL;

	public:
		JCoderMalfunctionError();

		JCoderMalfunctionError(JException* cause);

		static jcpp::lang::JClass* getClazz();

		virtual ~JCoderMalfunctionError();
	};

		}
	}
}



#endif /* JCODERMALFUNCTIONERROR_H_ */
