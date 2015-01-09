#include "jcpp/nio/charset/JUnsupportedCharsetException.h"


namespace jcpp {
	namespace nio {
		namespace charset {

	JUnsupportedCharsetException::JUnsupportedCharsetException():JIllegalArgumentException(getClazz()){
	}

	JUnsupportedCharsetException::JUnsupportedCharsetException(JString* charsetName)
		: JIllegalArgumentException(getClazz()){
		this->charsetName = charsetName;
		setMessage(charsetName);
	}

	JString* JUnsupportedCharsetException::getCharsetName(){
		return charsetName;
	}

	JUnsupportedCharsetException::~JUnsupportedCharsetException()
	{	}


		}
	}
}

