#ifndef JCPP_NIO_CS_JUTF_8_H
#define JCPP_NIO_CS_JUTF_8_H

#include "jcpp/nio/cs/JUnicode.h"
#include "jcpp/nio/cs/JArrayEncoder.h"
#include "jcpp/nio/cs/JArrayDecoder.h"
#include "jcpp/nio/cs/JSurrogate.h"

namespace jcpp {
	namespace nio {
		namespace cs {

	// @Class(canonicalName="sun.nio.cs.UTF_8", simpleName="UTF_8");
	class JCPP_EXPORT JUTF_8 : public JUnicode {
	public:
		JUTF_8();

		static jcpp::lang::JClass* getClazz();

		virtual JString* historicalName();

		virtual JCharsetEncoder* newEncoder();

		virtual JCharsetDecoder* newDecoder();

		static void updatePositions(JBuffer* src, jint sp, JBuffer* dst, jint dp);

		virtual ~JUTF_8();

		// @Class(canonicalName="sun.nio.cs.UTF_8.Encoder", simpleName="Encoder");
		class JCPP_EXPORT JEncoder : public JCharsetEncoder, public JArrayEncoder {
		private:
			JEncoder(JCharset* cs);

			static JCoderResult* overflow(JCharBuffer* src, jint sp, JByteBuffer* dst, jint dp);

			static JCoderResult* overflow(JCharBuffer* src, jint mark);

			JSurrogate::JParser* sgp;

			JCoderResult* encodeArrayLoop(JCharBuffer* src, JByteBuffer* dst);

			JCoderResult* encodeBufferLoop(JCharBuffer* src, JByteBuffer* dst);

		protected:
			virtual JCoderResult* encodeLoop(JCharBuffer* src, JByteBuffer* dst);

		public:
			static jcpp::lang::JClass* getClazz();

			jbool canEncode(jchar c);

			virtual jbool isLegalReplacement(JPrimitiveByteArray* repl);

			virtual jint encode(JPrimitiveCharArray* sa, jint sp, jint len, JPrimitiveByteArray* da);

			virtual ~JEncoder();

			friend class JUTF_8;
		};

		// @Class(canonicalName="sun.nio.cs.UTF_8.Decoder", simpleName="Decoder");
		class JCPP_EXPORT JDecoder : public JCharsetDecoder, public JArrayDecoder {
		public:
			JDecoder(JCharset* cs);
		private:
			static jbool isNotContinuation(jint b);
			static jbool isMalformed2(jint b1, jint b2);
			static jbool isMalformed3(jint b1, jint b2, jint b3);
			static jbool isMalformed4(jint b2, jint b3, jint b4);
			static JCoderResult* lookupN(JByteBuffer* src, jint n);
			static JCoderResult* malformedN(JByteBuffer* src, jint nb);
			static JCoderResult* malformed(JByteBuffer* src, jint sp, JCharBuffer* dst, jint dp, jint nb);
			static JCoderResult* malformed(JByteBuffer* src, jint mark, jint nb);
			static JCoderResult* xflow(JBuffer* src, jint sp, jint sl, JBuffer* dst, jint dp, jint nb);
			static JCoderResult* xflow(JBuffer* src, jint mark, jint nb);

			JCoderResult* decodeArrayLoop(JByteBuffer* src, JCharBuffer* dst);
			JCoderResult* decodeBufferLoop(JByteBuffer* src, JCharBuffer* dst);
			JByteBuffer* getByteBuffer(JByteBuffer* bb, JPrimitiveByteArray* ba, jint sp);

		protected:
			virtual JCoderResult* decodeLoop(JByteBuffer* src, JCharBuffer* dst);

		public:
			virtual jint decode(JPrimitiveByteArray* sa, jint sp, jint len, JPrimitiveCharArray* da);

			static jcpp::lang::JClass* getClazz();

			virtual ~JDecoder();
		};

	};


		}
	}
}



#endif /* JUTF_8_H_ */
