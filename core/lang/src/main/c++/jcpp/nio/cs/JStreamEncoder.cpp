#include "jcpp/nio/cs/JStreamEncoder.h"
#include <cassert>

namespace jcpp {
	namespace nio {
		namespace cs {

	const jint JStreamEncoder::DEFAULT_BYTE_BUFFER_SIZE = 8192;

	void JStreamEncoder::ensureOpen(){
		if (!_isOpen)
			throw new JIOException(new JString("Stream closed"));
	}

	JStreamEncoder* JStreamEncoder::forOutputStreamWriter(JOutputStream* out, JObject* lock, JString* charsetName)
	{
		JString* csn = charsetName;
		if (csn == null)
			csn = JCharset::defaultCharset()->getName();
		try {
			if (JCharset::isSupported(csn))
				return new JStreamEncoder(out, lock, JCharset::forName(csn));
		} catch(JIllegalCharsetNameException* x){	}
		throw new JUnsupportedEncodingException(csn);
	}

	JStreamEncoder* JStreamEncoder::forOutputStreamWriter(JOutputStream* out, JObject* lock, JCharset* cs)
	{
		return new JStreamEncoder(out, lock, cs);
	}

	JStreamEncoder* JStreamEncoder::forOutputStreamWriter(JOutputStream* out, JObject* lock, JCharsetEncoder* enc)
	{
		return new JStreamEncoder(out, lock, enc);
	}

	JString* JStreamEncoder::getEncoding()
	{
		if (isOpen())
			return encodingName();
		return null;
	}

	void JStreamEncoder::flushBuffer()
	{
		synchronized(lock, {
				if (isOpen())
					implFlushBuffer();
				else
					throw new JIOException(new JString("Stream closed"));
		})
	}

	void JStreamEncoder::write(jint c)
	{
		JPrimitiveCharArray* cbuf = new JPrimitiveCharArray(1);
		cbuf->setChar(0, (jchar)c);
		write(cbuf, 0, 1);
	}

	void JStreamEncoder::write(JPrimitiveCharArray* cbuf, jint off, jint len)
	{
		synchronized(lock, {
				ensureOpen();
				if ((off < 0) || (off > cbuf->size()) || (len < 0) ||
					((off + len) > cbuf->size()) || ((off+len) < 0)) {
					throw new JIndexOutOfBoundsException();
				} else if (len == 0){
					return;
				}
				implWrite(cbuf, off, len);
		})
	}

	void JStreamEncoder::write(JString* str, jint off, jint len)
	{
		if (len <  0)
			throw new JIndexOutOfBoundsException();
		JPrimitiveCharArray* cbuf = new JPrimitiveCharArray(len);
		str->getChars(off, off+len, cbuf, 0);
		write(cbuf, 0, len);
	}

	void JStreamEncoder::flush()
	{
		synchronized(lock, {
				ensureOpen();
				implFlush();
		})
	}

	void JStreamEncoder::close()
	{
		synchronized(lock, {
				if (!_isOpen)
					return;
				implClose();
				_isOpen = false;
		})
	}

	jbool JStreamEncoder::isOpen()
	{
		return _isOpen;
	}

	JStreamEncoder::JStreamEncoder(JOutputStream* out, JObject* lock, JCharset* cs)
		: JWriter(getClazz(), lock)
	{
		this->out = out;
		this->encoder = cs->newEncoder()->onMalformedInput(JCodingErrorAction::REPLACE)->onUnmappableCharacter(JCodingErrorAction::REPLACE);
		this->cs = encoder->getCharset();
		this->_isOpen = true;
		this->lcb = 0;
		this->haveLeftoverChar = false;
		this->lcb = null;
		//TODO ch

		bb = JByteBuffer::allocate(DEFAULT_BYTE_BUFFER_SIZE);
	}

	JStreamEncoder::JStreamEncoder(JOutputStream* out, JObject* lock, JCharsetEncoder* enc)
		:	JWriter(getClazz(), lock)
	{
		this->out = out;
		this->cs = enc->getCharset();
		this->encoder = enc;
		this->_isOpen = true;
		this->haveLeftoverChar = false;
		this->lcb = null;

		bb = JByteBuffer::allocate(DEFAULT_BYTE_BUFFER_SIZE);
	}

	void JStreamEncoder::writeBytes()
	{
		bb->flip();
		jint lim = bb->limit();
		jint pos = bb->position();
		assert(pos <= lim);
		jint rem = (pos <= lim ? lim - pos : 0);

		//TODO ch
		if (rem > 0){
			out->write((JPrimitiveByteArray*)bb->array(), bb->arrayOffset()+pos, rem);
		}
		bb->clear();
	}

	void JStreamEncoder::flushLeftoverChar(JCharBuffer* cb, jbool endOfInput)
	{
		if (!haveLeftoverChar && !endOfInput)
			return;


		if (lcb == null){
			lcb = JCharBuffer::allocate(2);
		}
		else{
			lcb->clear();
		}

		if (haveLeftoverChar){
			lcb->put(leftoverChar);
		}

		if ((cb != null) && cb->hasRemaining()){
			lcb->put(cb->get());
		}

		lcb->flip();
		while(lcb->hasRemaining() || endOfInput) {
			JCoderResult* cr = encoder->encode(lcb, bb, endOfInput);
			if (cr->isUnderflow()) {
				if (lcb->hasRemaining()) {
					leftoverChar = lcb->get();
					if (cb != null && cb->hasRemaining())
						flushLeftoverChar(cb, endOfInput);
					return;
				}
				break;
			}
			if (cr->isOverflow()) {
				assert(bb->position() > 0);
				writeBytes();
				continue;
			}
			cr->throwException();
		}
		haveLeftoverChar = false;
	}

	void JStreamEncoder::implWrite(JPrimitiveCharArray* cbuf, jint off, jint len)
	{
		JCharBuffer* cb = JCharBuffer::wrap(cbuf, off, len);

		if (haveLeftoverChar)
			flushLeftoverChar(cb, false);

		while (cb->hasRemaining()) {
			JCoderResult* cr = encoder->encode(cb, bb, false);
			if (cr->isUnderflow()) {
				assert(cb->remaining() <= 1);
				if (cb->remaining() == 1){
					haveLeftoverChar = true;
					leftoverChar = cb->get();
				}
				break;
			}
			if (cr->isOverflow()) {
				assert(bb->position() > 0);
				writeBytes();
				continue;
			}
			cr->throwException();
		}
	}

	void JStreamEncoder::implFlushBuffer()
	{
		if (bb->position() > 0)
			writeBytes();
	}

	void JStreamEncoder::implFlush()
	{
		implFlushBuffer();
		if (out != null)
			out->flush();
	}

	void JStreamEncoder::implClose()
	{
		flushLeftoverChar(null, true);
		try {
			for (;;) {
				JCoderResult* cr = encoder->flush(bb);
				if (cr->isUnderflow())
					break;
				if (cr->isOverflow()){
					assert(bb->position() > 0);
					writeBytes();
					continue;
				}
				cr->throwException();
			}

			if (bb->position() > 0)
				writeBytes();
			out->close();

		} catch (JIOException* x){
			encoder->reset();
			throw x;
		}
	}

	JString* JStreamEncoder::encodingName() {
		return cs->getName();
	}


		}
	}
}
