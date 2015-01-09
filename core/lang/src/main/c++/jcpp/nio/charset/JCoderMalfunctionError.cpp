#include "jcpp/nio/charset/JCoderMalfunctionError.h"



namespace jcpp {
	namespace nio {
		namespace charset {

	JCoderMalfunctionError::JCoderMalfunctionError():JError(getClazz())
	{	}

	JCoderMalfunctionError::JCoderMalfunctionError(JException* cause)
		: JError(getClazz(), cause)
	{	}

	JCoderMalfunctionError::~JCoderMalfunctionError()
	{	}


		}
	}
}

