#include "jcpp/nio/charset/JUnmappableCharacterException.h"


namespace jcpp {
	namespace nio {
		namespace charset {

	JUnmappableCharacterException::JUnmappableCharacterException() : JCharacterCodingException(getClazz()){
	}

	JUnmappableCharacterException::JUnmappableCharacterException(JPrimitiveInt* inputLength) : JCharacterCodingException(getClazz())
	{
		this->inputLength = inputLength;
		JStringBuilder* msg = new JStringBuilder(new JString("Input length = "));
		msg->append(inputLength);
		setMessage(msg->toString());
	}

	JPrimitiveInt* JUnmappableCharacterException::getInputLength(){
		return this->inputLength;
	}

	JUnmappableCharacterException::~JUnmappableCharacterException()
	{	}



		}
	}
}


