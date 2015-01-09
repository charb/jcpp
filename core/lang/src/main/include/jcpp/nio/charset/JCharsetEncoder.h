#ifndef JCPP_NIO_CHARSET_JCHARSETENCODER_H
#define JCPP_NIO_CHARSET_JCHARSETENCODER_H

#include "jcpp/native/api/NativeInclude.h"
#include "jcpp/nio/charset/JCodingErrorAction.h"
#include "jcpp/nio/charset/JCoderResult.h"
#include "jcpp/nio/JCharBuffer.h"
#include "jcpp/nio/JByteBuffer.h"
#include "jcpp/lang/JPrimitiveByteArray.h"
#include "jcpp/lang/JString.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/nio/charset/JCoderMalfunctionError.h"
#include "jcpp/lang/JArrayIndexOutOfBoundsException.h"

#include <cassert>

namespace jcpp {
	namespace nio {
		namespace charset {

	class JCharset;

	// @Class(canonicalName="java.nio.charset.CharsetEncoder", simpleName="CharsetEncoder");
	class JCPP_EXPORT JCharsetEncoder : public JObject {
	private:
		JCharset* charset;
		jfloat averageBytesPerChar;
		jfloat maxBytesPerChar;

		JPrimitiveByteArray* replacement;
		JCodingErrorAction* malformedInputAction;
		JCodingErrorAction* unmappableCharacterAction;

		static const jint ST_RESET = 0;
		static const jint ST_CODING = 1;
		static const jint ST_END = 2;
		static const jint ST_FLUSHED = 3;

		jint state;

		void construct(JCharset* cs, jfloat averageBytesPerChar, jfloat maxBytesPerChar, JPrimitiveByteArray* replacement);
		void throwIllegalStateException(jint from, jint to);
		JString* getStateNameFromID(jint id);


	protected:
		JCharsetEncoder(jcpp::lang::JClass* _class, JCharset* cs, jfloat averageBytesPerChar, jfloat maxBytesPerChar, JPrimitiveByteArray* replacement);
		JCharsetEncoder(jcpp::lang::JClass* _class, JCharset* cs, jfloat averageBytesPerChar, jfloat maxBytesPerChar);

		virtual void implReplaceWith(JPrimitiveByteArray* newReplacement);
		virtual void implOnMalformedInput(const JCodingErrorAction* newAction);
		virtual void implOnUnmappableCharacter(const JCodingErrorAction* newAction);
		virtual JCoderResult* implFlush(JByteBuffer* out);
		virtual void implReset();

		virtual JCoderResult* encodeLoop(JCharBuffer* src, JByteBuffer* dst) = 0;

	public:
		virtual ~JCharsetEncoder();
		static jcpp::lang::JClass* getClazz();

		JCharset* getCharset();
		JPrimitiveByteArray* getReplacement();
		JCharsetEncoder* replaceWith(JPrimitiveByteArray* newReplacement);
		virtual jbool isLegalReplacement(JPrimitiveByteArray* repl);
		jfloat getAverageBytesPerChar();
		jfloat getMaxBytesPerChar();
		JCharsetEncoder* onMalformedInput(const JCodingErrorAction* newAction);
		JCharsetEncoder* onUnmappableCharacter(const JCodingErrorAction* newAction);
		JCodingErrorAction* getMalformedInputAction();
		JCoderResult* encode(JCharBuffer* in, JByteBuffer* out, jbool endOfInput);
		JCoderResult* flush(JByteBuffer* out);
		JCharsetEncoder* reset();

		JByteBuffer* encode(JCharBuffer* in);

	};


		}
	}
}

#endif
