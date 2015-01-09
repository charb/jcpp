#ifndef JCPP_NIO_CS_JSTREAMENCODER_H
#define JCPP_NIO_CS_JSTREAMENCODER_H

#include "jcpp/io/JWriter.h"
#include "jcpp/nio/charset/JCharset.h"
#include "jcpp/nio/JByteBuffer.h"
#include "jcpp/io/JOutputStream.h"
#include "jcpp/io/JIOException.h"
#include "jcpp/io/JUnsupportedEncodingException.h"
#include "jcpp/io/JFileOutputStream.h"


namespace jcpp {
	namespace nio {
		namespace cs {

	using namespace jcpp::nio::charset;
	using namespace jcpp::io;

	// @Class(canonicalName="sun.nio.cs.StreamEncoder", simpleName="StreamEncoder");
	class JCPP_EXPORT JStreamEncoder : public JWriter
	{
	private:
		static const jint DEFAULT_BYTE_BUFFER_SIZE;
		/*volatile*/ jbool _isOpen;

		JCharset* cs;
		JCharsetEncoder* encoder;
		JByteBuffer* bb;

		JOutputStream* out;

		jbool haveLeftoverChar;
		jchar leftoverChar;
		JCharBuffer* lcb;

		void ensureOpen();
		jbool isOpen();

		JStreamEncoder(JOutputStream* out, JObject* lock, JCharset* cs);
		JStreamEncoder(JOutputStream* out, JObject* lock, JCharsetEncoder* enc);

		void writeBytes();
		void flushLeftoverChar(JCharBuffer* cb, jbool endOfInput);

	public:
		static jcpp::lang::JClass* getClazz();

		static JStreamEncoder* forOutputStreamWriter(JOutputStream* out, JObject* lock, JString* charsetName);
		static JStreamEncoder* forOutputStreamWriter(JOutputStream* out, JObject* lock, JCharset* cs);
		static JStreamEncoder* forOutputStreamWriter(JOutputStream* out, JObject* lock, JCharsetEncoder* enc);

		JString* getEncoding();
		void flushBuffer();
		void write(jint c);
		void write(JPrimitiveCharArray* cbuf, jint off, jint len);
		void write(JString* str, jint off, jint len);
		void flush();
		void close();

		void implWrite(JPrimitiveCharArray* cbuf, jint off, jint len);
		void implFlushBuffer();
		void implFlush();
		void implClose();
		JString* encodingName();

	};

		}
	}
}



#endif /* JSTREAMENCODER_H_ */
