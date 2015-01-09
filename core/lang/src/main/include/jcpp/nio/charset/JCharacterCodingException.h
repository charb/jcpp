#ifndef JCPP_NIO_CHARSET_JCHARACTERCODINGEXCEPTION_H
#define JCPP_NIO_CHARSET_JCHARACTERCODINGEXCEPTION_H

#include "jcpp/io/JIOException.h"
#include "jcpp/lang/reflect/JModifier.h"

namespace jcpp {
	namespace nio {
		namespace charset {

		// @Class(canonicalName="java.nio.charset.CharacterCodingException", simpleName="CharacterCodingException");
		class JCPP_EXPORT JCharacterCodingException : public JIOException {
		private:
			static const jlong serialVersionUID = 8421532232154627783LL;

		protected:
			JCharacterCodingException(jcpp::lang::JClass* _class);

		public:
			JCharacterCodingException();

			static jcpp::lang::JClass* getClazz();

			virtual ~JCharacterCodingException();

		};

		}
	}
}


#endif /* JCHARACTERCODINGEXCEPTION_H_ */
