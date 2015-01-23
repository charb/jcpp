#include "jcpp/nio/cs/JStreamDecoder.h"
#include "jcpp/io/JIOException.h"
#include "jcpp/io/JUnsupportedEncodingException.h"
#include <cassert>

namespace jcpp {
	namespace nio {
		namespace cs {

		const jint JStreamDecoder::MIN_BYTE_BUFFER_SIZE = 32;
		const jint JStreamDecoder::DEFAULT_BYTE_BUFFER_SIZE = 8192;
		jbool JStreamDecoder::channelsAvailable = true;

		void JStreamDecoder::ensureOpen() {
			if (!_isOpen)
				throw new JIOException(new JString("Stream closed"));
		}

		JStreamDecoder* JStreamDecoder::forInputStreamReader(JInputStream* in, JObject* lock, JString* charsetName) {
			JString* csn = charsetName;
			if (csn == null)
				csn = JCharset::defaultCharset()->getName();
			try {
				if (JCharset::isSupported(csn))
					return new JStreamDecoder(in, lock, JCharset::forName(csn));
			} catch (JIllegalCharsetNameException* x) { }
			throw new JUnsupportedEncodingException(csn);
		}

		JStreamDecoder* JStreamDecoder::forInputStreamReader(JInputStream* in, JObject* lock, JCharset* cs) {
			return new JStreamDecoder(in, lock, cs);
		}

		JStreamDecoder* JStreamDecoder::forInputStreamReader(JInputStream* in, JObject* lock, JCharsetDecoder* dec) {
			return new JStreamDecoder(in, lock, dec);
		}

		JStreamDecoder* JStreamDecoder::forDecoder(JReadableByteChannel* ch, JCharsetDecoder* dec, jint minBufferCap) {
			return new JStreamDecoder(ch, dec, minBufferCap);
		}

		JString* JStreamDecoder::getEncoding() {
			if (isOpen())
				return encodingName();
			return null;
		}

		jint JStreamDecoder::read() {
			return read0();
		}

		jint JStreamDecoder::read0() {
			synchronized(lock,

				//Return the leftover char, if there is one
				if (haveLeftoverChar){
					haveLeftoverChar = false;
					return leftoverChar;
				}

				//Convert more bytes
				JPrimitiveCharArray* cb = new JPrimitiveCharArray(2);
				jint n = read(cb, 0, 2);
				switch (n) {
				case -1:
					return -1;
				case 2:
					leftoverChar = cb->getChar(1);
					haveLeftoverChar = true;
					//fall through
				case 1:
					return cb->getChar(0);
				default:
					assert(false);
					return -1;
				}
			);
		}

		jint JStreamDecoder::read(JPrimitiveCharArray* cbuf, jint offset, jint length) {
			jint off = offset;
			jint len = length;
			synchronized(lock,
				ensureOpen();
				if ((off < 0) || (off > cbuf->size()) || (len < 0) ||
					((off + len) > cbuf->size()) || ((off + len) < 0)) {
					throw new JIndexOutOfBoundsException();
				}
				if (len == 0)
					return 0;

				jint n = 0;

				if (haveLeftoverChar) {
					//Copy the leftover char into the buffer
					cbuf->setChar(off, leftoverChar);
					off++; len--;
					haveLeftoverChar = false;
					n = 1;
					if ((len == 0) || !implReady())
						return n;
				}

				if (len == 1) {
					jint c = read0();
					if (c == -1)
						return (n == 0) ? -1 : n;
					cbuf->setChar(off, (jchar)c);
					return n+1;
				}

				return n + implRead(cbuf, off, off + len);
			);
		}

		jbool JStreamDecoder::ready() {
			synchronized(lock,
				ensureOpen();
				return haveLeftoverChar || implReady();
			);
		}

		void JStreamDecoder::close() {
			synchronized(lock,
				if (!_isOpen)
					return;
				implClose();
				_isOpen = false;
			);
		}

		jbool JStreamDecoder::isOpen() {
			return _isOpen;
		}

		JFileChannel* JStreamDecoder::getChannel(JFileInputStream* in) {
			//TODO
/*			if (!channelsAvailable)
				return null;
			try {
				return in->getChannel();
			} catch (JUnsatisfiedLinkError* x){
				channelsAvailable = false;
				return null;
			}*/
			return null;
		}


		JStreamDecoder::JStreamDecoder(JInputStream* in, JObject* lock, JCharset* cs) : JReader(getClazz(), lock), ch(null){
			this->_isOpen = true;
			this->haveLeftoverChar = false;
			this->channelsAvailable = true;

			this->decoder = cs->newDecoder()->onMalformedInput(JCodingErrorAction::REPLACE)->onUnmappableCharacter(JCodingErrorAction::REPLACE);
			this->cs = this->decoder->getCharset();

//TODO
/*			if (false && in->isInstanceOf(JFileInputStream::getClazz())){
				ch = getChannel((JFileInputStream*)in);
				if (ch != null)
					bb = JByteBuffer::allocateDirect(DEFAULT_BYTE_BUFFER_SIZE);
			}*/
			if (ch == null) {
				this->in = in;
				this->ch = null;
				bb = JByteBuffer::allocate(DEFAULT_BYTE_BUFFER_SIZE);
			}
			bb->flip();
		}

		JStreamDecoder::JStreamDecoder(JInputStream* in, JObject* lock, JCharsetDecoder* dec) : JReader(getClazz(), lock) {
			this->_isOpen = true;
			this->haveLeftoverChar = false;
			this->channelsAvailable = true;

			this->decoder = dec;
			this->cs = dec->getCharset();

			if (false && in->isInstanceOf(JFileInputStream::getClazz())){
			ch = (JByteChannel*)getChannel((JFileInputStream*)in);
			if (ch != null)
				bb = JByteBuffer::allocate(DEFAULT_BYTE_BUFFER_SIZE); //TODO use allocateDirect
			}
			if (ch == null) {
			this->in = in;
			this->ch = null;
			bb = JByteBuffer::allocate(DEFAULT_BYTE_BUFFER_SIZE);
			}
			bb->flip();
		}

		JStreamDecoder::JStreamDecoder(JReadableByteChannel* ch, JCharsetDecoder* dec, jint mbc) : JReader(getClazz(), null) {
			this->_isOpen = true;
			this->haveLeftoverChar = false;
			this->channelsAvailable = true;

			this->in = null;
			this->ch = ch;
			this->decoder = dec;
			this->cs = dec->getCharset();
			this->bb = JByteBuffer::allocate(mbc < 0 ? DEFAULT_BYTE_BUFFER_SIZE :
											(mbc < MIN_BYTE_BUFFER_SIZE? MIN_BYTE_BUFFER_SIZE : mbc));
			bb->flip();
		}

		jint JStreamDecoder::readBytes() {
			bb->compact();
			try {
				if (ch != null) {
					jint n = ch->read(bb);
					if (n < 0)
						return n;
				}else {
					jint lim = bb->limit();
					jint pos = bb->position();
					assert (pos <= lim);
					jint rem = (pos <= lim? lim-pos : 0);
					assert(rem > 0);
					jint n = in->read((JPrimitiveByteArray*)bb->array(), bb->arrayOffset()+pos, rem);
					if (n<0) {
						bb->flip();
						return n;
					}
					if (n==0)
						throw new JIOException(new JString("Underlying input stream returned zero bytes"));
					assert(n <= rem);
					bb->position(pos+n);
				}
			} catch(JException* x){}
			bb->flip();

			jint rem = bb->remaining();
//			assert(rem!=0); //TODO check other asserts
			return rem;
		}

		jint JStreamDecoder::implRead(JPrimitiveCharArray* cbuf, jint off, jint end) {
			assert(end-off > 1);

			JCharBuffer* cb = JCharBuffer::wrap(cbuf, off, end-off);
			if (cb->position() != 0)
				cb = cb->slice();

			jbool eof = false;
			for (;;){
				JCoderResult* cr = this->decoder->decode(bb, cb, eof);
				if (cr->isUnderflow()){
					if (eof)
						break;
					if (!cb->hasRemaining())
						break;
					if ((cb->position()>0) && !inReady())
						break;
					jint n = readBytes();
					if (n < 0) {
						eof = true;
						if ((cb->position()==0) && (!bb->hasRemaining()))
							break;
						decoder->reset();
					}
					continue;
				}
				if (cr->isOverflow()){
					assert(cb->position() > 0);
					break;
				}
				cr->throwException();
			}

			if (eof) {
				decoder->reset();
			}

			if (cb->position() == 0){
				if (eof)
					return -1;
				assert(false);
			}
			return cb->position();
		}

		JString* JStreamDecoder::encodingName() {
			return ((cs->isInstanceOf(JHistoricallyNamedCharset::getClazz()))?
					  ((JHistoricallyNamedCharset*)cs)->historicalName() : cs->getName());
		}

		jbool JStreamDecoder::inReady() {
			try {
				return (((in != null) && (in->available() > 0))
						|| (ch->getClazz()->isInstance(JFileChannel::getClazz())));
			} catch(JIOException* x) {
				return false;
			}
		}

		jbool JStreamDecoder::implReady() {
			return bb->hasRemaining() || inReady();
		}

		void JStreamDecoder::implClose() {
			if (ch != null)
				ch->close();
			else
				in->close();
		}


		}
	}
}
