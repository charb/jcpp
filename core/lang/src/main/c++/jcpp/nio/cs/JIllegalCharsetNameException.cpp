#include "jcpp/nio/cs/JIllegalCharsetNameException.h"

namespace jcpp {
	namespace nio {
		namespace cs {

			JIllegalCharsetNameException::JIllegalCharsetNameException() :JIllegalArgumentException(getClazz()) {
			}

			JIllegalCharsetNameException::JIllegalCharsetNameException(JString* charsetName) :JIllegalArgumentException(getClazz()) {
				this->detailMessage = charsetName;
				this->charsetName = charsetName;
			}

			JString* JIllegalCharsetNameException::getCharsetName() {
				return charsetName;
			}

			JIllegalCharsetNameException::~JIllegalCharsetNameException() {
			}
		}
	}
}
