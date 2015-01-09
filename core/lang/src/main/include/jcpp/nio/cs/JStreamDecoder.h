#ifndef JCPP_NIO_CS_JSTREAMDECODER_H
#define JCPP_NIO_CS_JSTREAMDECODER_H

#include "jcpp/io/JReader.h"
#include "jcpp/nio/charset/JCharset.h"
#include "jcpp/nio/JByteBuffer.h"
#include "jcpp/io/JInputStream.h"
#include "jcpp/nio/channels/JReadableByteChannel.h"
#include "jcpp/nio/channels/JFileChannel.h"
#include "jcpp/io/JFileInputStream.h"
#include "jcpp/lang/JUnsatisfiedLinkError.h"
#include "jcpp/nio/cs/JHistoricallyNamedCharset.h"

using namespace jcpp::io;
using namespace jcpp::nio::charset;
using namespace jcpp::nio::channels;

namespace jcpp {
	namespace nio {
		namespace cs {

		// @Class(canonicalName="sun.nio.cs.StreamDecoder", simpleName="StreamDecoder");
		class JCPP_EXPORT JStreamDecoder : public JReader
		{
		private:
			static const jint MIN_BYTE_BUFFER_SIZE;
			static const jint DEFAULT_BYTE_BUFFER_SIZE;

			/*volatile*/ jbool _isOpen; //TODO check how to implement volatile

			jbool haveLeftoverChar;
			jchar leftoverChar;

			static /*volatile*/ jbool channelsAvailable;

			JCharset* cs;
			JCharsetDecoder* decoder;
			JByteBuffer* bb;

			JInputStream* in;
			JReadableByteChannel* ch;

		public:
			static jcpp::lang::JClass* getClazz();

			void ensureOpen();
			static JStreamDecoder* forInputStreamReader(JInputStream* in, JObject* lock, JString* charsetName);
			static JStreamDecoder* forInputStreamReader(JInputStream* in, JObject* lock, JCharset* cs);
			static JStreamDecoder* forInputStreamReader(JInputStream* in, JObject* lock, JCharsetDecoder* dec);
			static JStreamDecoder* forDecoder(JReadableByteChannel* ch, JCharsetDecoder* dec, jint minBufferCap);
			JString* getEncoding();
			jint read();
			jint read0();
			jint read(JPrimitiveCharArray* cbuf, jint offset, jint length);
			jbool ready();
			void close();
			jbool isOpen();
			static JFileChannel* getChannel(JFileInputStream* in);

		private:
			JStreamDecoder(JInputStream* in, JObject* lock, JCharset* cs);
			JStreamDecoder(JInputStream* in, JObject* lock, JCharsetDecoder* dec);
			JStreamDecoder(JReadableByteChannel* ch, JCharsetDecoder* dec, jint mbc);
			jint readBytes();
			jint implRead(JPrimitiveCharArray* cbuf, jint off, jint end);
			JString* encodingName();
			jbool inReady();
			jbool implReady();
			void implClose();

		};

		}
	}
}


#endif /* JSTREAMDECODER_H_ */
