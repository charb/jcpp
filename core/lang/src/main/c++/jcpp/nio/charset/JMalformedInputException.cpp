#include "jcpp/nio/charset/JMalformedInputException.h"


namespace jcpp {
	namespace nio {
		namespace charset {

	JMalformedInputException::JMalformedInputException() : JCharacterCodingException(getClazz()){
		setMessage(new JString("Malformed Input Exception"));
	}

	JMalformedInputException::JMalformedInputException(JPrimitiveInt* inputLength) : JCharacterCodingException(getClazz())
	{
		this->inputLength = inputLength;
		JStringBuilder* msg = new JStringBuilder(new JString("Malformed Input Exception, inputLenght="));
		msg->append(inputLength);
		setMessage(msg->toString());
	}

	JPrimitiveInt* JMalformedInputException::getInputLength(){
		return this->inputLength;
	}


	JMalformedInputException::~JMalformedInputException()
	{	}


		}
	}
}

