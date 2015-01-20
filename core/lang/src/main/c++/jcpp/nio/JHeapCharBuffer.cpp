#include "jcpp/nio/JHeapCharBuffer.h"


namespace jcpp {
	namespace nio {

	JHeapCharBuffer::JHeapCharBuffer(jint cap, jint lim)
	: JCharBuffer(getClazz(), -1, 0, lim, cap,new JPrimitiveCharArray(cap), 0)
	{
	}

	JHeapCharBuffer::JHeapCharBuffer(JPrimitiveCharArray* buf, jint off, jint len)
	: JCharBuffer(getClazz(), -1, off, off+len, buf->size(), buf, 0)
	{
	}


	JHeapCharBuffer::JHeapCharBuffer(JPrimitiveCharArray* buf, jint mark, jint pos, jint lim, jint cap, jint off)
	: JCharBuffer(getClazz(), mark, pos, lim, cap, buf, off)
	{
	}

	jint JHeapCharBuffer::ix(jint i)
	{
		return i + offset;
	}

	jchar JHeapCharBuffer::get()
	{
		return hb->getChar(ix(nextGetIndex()));
	}

	jchar JHeapCharBuffer::get(jint i)
	{
		return hb->getChar(ix(checkIndex(i)));
	}

	JCharBuffer* JHeapCharBuffer::get(JPrimitiveCharArray* dst, jint offset, jint length)
	{
		checkBounds(offset, length, dst->size());
		if (length > remaining())
			throw new JBufferUnderflowException();
		for (int i=offset; i < offset+length; i++){
			dst->setChar(i, this->get(position()));
			position(position()+1);
		}
		return this;
	}

	jbool JHeapCharBuffer::isDirect()
	{
		return false;
	}

	JCharBuffer* JHeapCharBuffer::put(jchar x)
	{
		hb->setChar(nextPutIndex(), x);
		return this;
	}

	JCharBuffer* JHeapCharBuffer::put(jint i, jchar x)
	{
		hb->setChar(checkIndex(i), x);
		return this;
	}

	JCharBuffer* JHeapCharBuffer::put(JPrimitiveCharArray* src, jint offset, jint length)
	{
		checkBounds(offset, length, src->size());
		if (length > remaining())
			throw new JBufferOverflowException();
		for (jint i = offset; i < offset+length; i++){
			hb->setChar(position(), src->getChar(i));
			position(position()+1);
		}
		return this;
	}

	JCharBuffer* JHeapCharBuffer::put(JCharBuffer* src)
	{
		if (src->isInstanceOf(JHeapCharBuffer::getClazz())){
			if (src == this)
				throw new JIllegalArgumentException();
			JHeapCharBuffer* sb = (JHeapCharBuffer*)src;
			jint n = sb->remaining();
			if (n > remaining())
				throw new JBufferOverflowException();
			JSystem::arraycopy(sb->hb, sb->ix(sb->position()), hb, ix(position()), n);
			sb->position(sb->position() + n);
			position(position() + n);
		} else if (src->isDirect()){
			jint n = src->remaining();
			if (n > remaining())
				throw new JBufferOverflowException();
			src->get(hb, ix(position()), n);
			position(position() + n);
		}else{
			JCharBuffer::put(src);
		}
		return this;
	}

	JCharBuffer* JHeapCharBuffer::slice() {
		return new JHeapCharBuffer(hb, -1, 0, this->remaining(), this->remaining(), this->position() + offset);
	}

	JString* JHeapCharBuffer::toString(jint start, jint end)
	{
		try{
			return new JString(hb, start+offset, end-start);
		} catch (JStringIndexOutOfBoundsException* x){
			throw new JIndexOutOfBoundsException();
		}
	}

	JCharBuffer* JHeapCharBuffer::subSequence(jint start, jint end)
	{
		if ((start < 0) || (end > length()) || (start > end))
			throw new JIndexOutOfBoundsException();
		jint pos = position();
		return new JHeapCharBuffer(hb, -1, pos+start, pos+end, capacity(), offset);
	}

	JByteOrder* JHeapCharBuffer::order()
	{
		if (NativeEndian::isBigEndian()){
			return JByteOrder::JBIG_ENDIAN;
		}else{
			return JByteOrder::JLITTLE_ENDIAN;
		}
	}


	JHeapCharBuffer::~JHeapCharBuffer()
	{	}



	}
}
