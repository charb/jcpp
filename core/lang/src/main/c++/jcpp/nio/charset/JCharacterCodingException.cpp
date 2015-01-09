#include "jcpp/nio/charset/JCharacterCodingException.h"


namespace jcpp {
	namespace nio {
		namespace charset {

		JCharacterCodingException::JCharacterCodingException() : JIOException(getClazz())
		{	}

		JCharacterCodingException::JCharacterCodingException(jcpp::lang::JClass* _class): JIOException(_class)
		{	}

		JCharacterCodingException::~JCharacterCodingException()
		{	}


		}
	}
}

