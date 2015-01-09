#include "jcpp/nio/JInvalidMarkException.h"


namespace jcpp {
	namespace nio {

	JInvalidMarkException::JInvalidMarkException():JIllegalStateException(getClazz())
	{	}

	JInvalidMarkException::~JInvalidMarkException()
	{	}



	}
}
