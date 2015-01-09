#include "jcpp/nio/JReadOnlyBufferException.h"


namespace jcpp {
	namespace nio {

	JReadOnlyBufferException::JReadOnlyBufferException():JUnsupportedOperationException(getClazz())
	{	}

	JReadOnlyBufferException::~JReadOnlyBufferException()
	{	}


	}
}
