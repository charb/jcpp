#ifndef JCPP_NIO_CHARSET_JUNSUPPORTEDCHARSETEXCEPTION_H
#define JCPP_NIO_CHARSET_JUNSUPPORTEDCHARSETEXCEPTION_H

#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/native/api/NativeInclude.h"
#include "jcpp/lang/JIllegalArgumentException.h"

namespace jcpp {
	namespace nio {
		namespace charset {

	// @Class(canonicalName="java.nio.charset.UnsupportedCharsetException", simpleName="UnsupportedCharsetException");
	class JCPP_EXPORT JUnsupportedCharsetException : public JIllegalArgumentException
	{
	private:
		static const jlong serialVersionUID = 1490765524727386367LL;

		JString* charsetName;

	public:
		JUnsupportedCharsetException();
		JUnsupportedCharsetException(JString* charsetName);

		JString* getCharsetName();

		static jcpp::lang::JClass* getClazz();

		virtual ~JUnsupportedCharsetException();

		friend class JUnsupportedCharsetExceptionClass;
	};


		}
	}
}



#endif /* JUNSUPPORTEDCHARSETEXCEPTION_H_ */
