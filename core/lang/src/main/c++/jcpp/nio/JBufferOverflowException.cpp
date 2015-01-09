#include "jcpp/nio/JBufferOverflowException.h"

namespace jcpp {
	namespace nio {

	JBufferOverflowException::JBufferOverflowException() : JRuntimeException(getClazz())
	{	}

	JBufferOverflowException::~JBufferOverflowException()
	{	}


	}
}
