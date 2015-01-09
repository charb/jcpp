#ifndef JCPP_LANG_JSTRINGCODING_H
#define JCPP_LANG_JSTRINGCODING_H

#include "jcpp/lang/JPrimitiveByteArray.h"
#include "jcpp/io/JUnsupportedEncodingException.h"
#include "jcpp/nio/cs/JIllegalCharsetNameException.h"
#include "jcpp/nio/charset/JCharacterCodingException.h"
#include "jcpp/nio/charset/JCharset.h"
#include "jcpp/nio/charset/JCharsetEncoder.h"
#include "jcpp/nio/cs/JArrayEncoder.h"
#include "jcpp/nio/cs/JArrayDecoder.h"
#include "jcpp/nio/JCharBuffer.h"
#include "jcpp/nio/JByteBuffer.h"
#include "jcpp/util/JArrays.h"
#include "jcpp/lang/JError.h"

using namespace jcpp::nio::charset;
using namespace jcpp::nio;

namespace jcpp{
	namespace lang{
		class JCPP_EXPORT JStringCoding  : public JObject{

		private:
			class JCPP_EXPORT JStringEncoder : JObject{
				private:
					JCharset* cs;
					JCharsetEncoder* ce;
					const JString* reqCharsetName;
					jbool isTrusted;
				public:
					JStringEncoder(JCharset* cs, JString* rcn);

					JString* charsetName();

					const JString* requestedCharsetName();

					JPrimitiveByteArray* encode(JPrimitiveCharArray* ca, jint off, jint len);
			};

			class JCPP_EXPORT JStringDecoder{
				private:
					const JString* reqCharsetName;
					JCharset* cs;
					JCharsetDecoder* cd;
					jbool isTrusted;

				public:
					JStringDecoder(JCharset* cs, JString* rcn);

					JString* charsetName();

					const JString* requestedCharsetName();

					JPrimitiveCharArray* decode(JPrimitiveByteArray* ba, jint off, jint len);
			};


		static JPrimitiveByteArray* safeTrim(JPrimitiveByteArray* ba, jint len, JCharset* cs, jbool isTrusted);
		static JPrimitiveCharArray* safeTrim(JPrimitiveCharArray* ca, jint len, JCharset* cs, jbool isTrusted);

		static jint scale(jint len, jfloat expansionFactor);
		static JCharset* lookupCharset(JString* csn);

		protected:

		public:
			virtual ~JStringCoding();

			JStringCoding();
			static jcpp::lang::JClass* getClazz();

			static JPrimitiveCharArray* decode(JString* charsetName, JPrimitiveByteArray* ba, jint off, jint len);
			static JPrimitiveCharArray* decode(JPrimitiveByteArray* ba, jint off, jint len);

			static JPrimitiveByteArray* encode(JString* charsetName, JPrimitiveCharArray* ca, jint off, jint len);
			static JPrimitiveByteArray* encode(JPrimitiveCharArray* ca, jint off, jint len);

		};
	}
}


#endif /* JSTRINGCODING_H_ */
