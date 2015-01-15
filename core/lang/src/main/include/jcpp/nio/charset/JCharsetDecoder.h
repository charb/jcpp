#ifndef JCPP_NIO_CHARSET_JCHARSETDECODER_H
#define JCPP_NIO_CHARSET_JCHARSETDECODER_H

#include "jcpp/native/api/NativeInclude.h"
#include "jcpp/nio/charset/JCodingErrorAction.h"
#include "jcpp/nio/charset/JCoderResult.h"
#include "jcpp/nio/JCharBuffer.h"
#include "jcpp/nio/JByteBuffer.h"
#include "jcpp/lang/JPrimitiveByteArray.h"
#include "jcpp/lang/JString.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/nio/charset/JCoderMalfunctionError.h"

#include <cassert>



namespace jcpp {
	namespace nio {
		namespace charset {

		class JCharset;

		// @Class(canonicalName="java.nio.charset.CharsetDecoder", simpleName="CharsetDecoder");
		class JCPP_EXPORT JCharsetDecoder : public JObject {
		private:
			JCharset* charset;
			jfloat averageCharsPerByte;
			jfloat maxCharsPerByte;

			JString* replacement;
			JCodingErrorAction* malformedInputAction;
			JCodingErrorAction* unmappableCharacterAction;

			static const jint ST_RESET = 0;
			static const jint ST_CODING = 1;
			static const jint ST_END = 2;
			static const jint ST_FLUSHED = 3;

			jint state;

			void construct(JCharset* cs, jfloat averageCharsPerByte, jfloat maxCharsPerByte, JString* replacement);
			void throwIllegalStateException(jint from, jint to);
			JString* getStateNameFromID(jint id);

		protected:
			JCharsetDecoder(jcpp::lang::JClass* _class, JCharset* cs, jfloat averageCharsPerByte, jfloat maxCharsPerByte, JString* replacement);
			JCharsetDecoder(jcpp::lang::JClass* _class, JCharset* cs, jfloat averageCharsPerByte, jfloat maxCharsPerByte);

			virtual void implReplaceWith(JString* newReplacement);
			virtual void implOnMalformedInput(const JCodingErrorAction* newAction);
			virtual void implOnUnmappableCharacter(const JCodingErrorAction* newAction);
			virtual JCoderResult* implFlush(JCharBuffer* out);
			virtual void implReset();

			virtual JCoderResult* decodeLoop(JByteBuffer* src, JCharBuffer* dst) = 0;

		public:
			virtual ~JCharsetDecoder();
			static jcpp::lang::JClass* getClazz();

			JCharset* getCharset();
			JString* getReplacement();
			JCharsetDecoder* replaceWith(JString* newReplacement);
			jfloat getAverageCharsPerByte();
			jfloat getMaxCharsPerByte();
			JCharsetDecoder* onMalformedInput(const JCodingErrorAction* newAction);
			JCharsetDecoder* onUnmappableCharacter(const JCodingErrorAction* newAction);
			JCodingErrorAction* getMalformedInputAction();
			JCoderResult* decode(JByteBuffer* in, JCharBuffer* out, jbool endOfInput);
			JCoderResult* flush(JCharBuffer* out);
			JCharsetDecoder* reset();
//			JCharBuffer* decode(JByteBuffer* in);

		};


		}
	}
}


#endif /* JCHARSETDECODER_H_ */
