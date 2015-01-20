#include "jcpp/nio/cs/JSurrogate.h"



namespace jcpp {
	namespace nio {
		namespace cs {

	JSurrogate::JSurrogate() : JObject(getClazz())
	{	}

	JSurrogate::JParser::JParser() : JObject(getClazz()), isPair(false), character(0) {
		_error = JCoderResult::JUNDERFLOW;
	}

	JCoderResult* JSurrogate::JParser::error()
	{
		assert(_error != null);
		return _error;
	}

	jint JSurrogate::JParser::parse(jchar c, JCharBuffer* in)
	{
		if (JCharacter::isHighSurrogate(c)){
			if (!in->hasRemaining()) {
				_error = JCoderResult::JUNDERFLOW;
				return -1;
			}
			jchar d = in->get();
			if (JCharacter::isLowSurrogate(d)){
				character = JCharacter::toCodePoint(c, d);
				isPair = true;
				_error = null;
				return character;
			}
			_error = JCoderResult::malformedForLength(1);
			return -1;
		}
		if (JCharacter::isLowSurrogate(c)) {
			_error = JCoderResult::malformedForLength(1);
			return -1;
		}
		character = c;
		isPair = false;
		_error = null;
		return character;
	}

	jint JSurrogate::JParser::parse(jchar c, JPrimitiveCharArray* ia, jint ip, jint il)
	{
		assert(ia->getChar(ip) == c);
		if (JCharacter::isHighSurrogate(c)) {
			if (il - ip < 2) {
			_error = JCoderResult::JUNDERFLOW;
			return -1;
			}
			jchar d = ia->getChar(ip+1);
			if (JCharacter::isLowSurrogate(d)) {
				character = JCharacter::toCodePoint(c, d);
				isPair = true;
				_error = null;
				return character;
			}
			_error = JCoderResult::malformedForLength(1);
			return -1;
		}
		if (JCharacter::isLowSurrogate(c)) {
			_error = JCoderResult::malformedForLength(1);
			return -1;
		}
		character = c;
		isPair = false;
		_error = null;
		return character;
	}

	JSurrogate::JParser::~JParser()
	{	}

	JSurrogate::~JSurrogate()
	{	}


		}
	}
}

