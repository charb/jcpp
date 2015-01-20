#include "jcpp/nio/charset/JCoderResult.h"
#include "jcpp/nio/JBufferUnderflowException.h"
#include "jcpp/nio/JBufferOverflowException.h"
#include "jcpp/nio/charset/JMalformedInputException.h"
#include "jcpp/nio/charset/JUnmappableCharacterException.h"
#include <assert.h>


namespace jcpp {
	namespace nio {
		namespace charset {

			JCoderResult* JCoderResult::JUNDERFLOW = new JCoderResult(CR_UNDERFLOW, 0);
			JCoderResult* JCoderResult::JOVERFLOW = new JCoderResult(CR_OVERFLOW, 0);


			JCoderResult::JCoderResult(jint type, jint length) : JObject(getClazz()), type(type), length(length) {
			}

			JCoderResult* JCoderResult::malformedForLength(jint length) {
				return new JCoderResult(CR_MALFORMED, length);
			}

			JString* JCoderResult::toString() {
				JString* nm = new JString(getErrorNameFromID(type));
				JStringBuilder* nmLen = new JStringBuilder(nm);
				nmLen->append("[");
				nmLen->append(length);
				nmLen->append("]");
				return isError()? nmLen->toString() : nm;
			}

			jbool JCoderResult::isUnderflow() {
				return (type == CR_UNDERFLOW);
			}

			jbool JCoderResult::isOverflow() {
				return (type == CR_OVERFLOW);
			}

			jbool JCoderResult::isError() {
				return (type >= CR_ERROR_MIN);
			}

			jbool JCoderResult::isMalformed() {
				return (type == CR_MALFORMED);
			}

			jbool JCoderResult::isUnmappable() {
				return (type == CR_UNMAPPABLE);
			}

			jint JCoderResult::getLength() {
				if (!isError())
					throw new JUnsupportedOperationException();
				return length;
			}

			void JCoderResult::throwException() {
				switch (type) {
				case CR_UNDERFLOW: throw new JBufferUnderflowException();
				case CR_OVERFLOW: throw new JBufferOverflowException();
				case CR_MALFORMED: throw new JMalformedInputException(new JPrimitiveInt(length));
				case CR_UNMAPPABLE: throw new JUnmappableCharacterException(new JPrimitiveInt(length));
				default:
					assert(false);
				}
			}

			JCoderResult::~JCoderResult() {

			}


			JString* JCoderResult::getErrorNameFromID(jint id) {
				switch(id){
				case 0:
					return new JString("UNDERFLOW");
				case 1:
					return new JString("OVERFLOW");
				case 2:
					return new JString("MALFORMED");
				case 3:
					return new JString("UNMAPPABLE");
				default:
					throw new JArrayIndexOutOfBoundsException(new JString("Invalid Error index"));
				}
			}

		}
	}
}
