#include "jcpp/nio/JBufferUnderflowException.h"


namespace jcpp {
	namespace nio {

	JBufferUnderflowException::JBufferUnderflowException() : JRuntimeException(getClazz())
	{	}

	JBufferUnderflowException::~JBufferUnderflowException()
	{	}


	}
}

