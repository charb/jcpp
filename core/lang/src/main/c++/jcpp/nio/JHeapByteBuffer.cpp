#include "jcpp/nio/JHeapByteBuffer.h"

using namespace jcpp::nio;

namespace jcpp {
	namespace nio {

		JHeapByteBuffer::JHeapByteBuffer(jint cap, jint lim)
			:JByteBuffer(getClazz(), -1, 0, lim, cap,new JPrimitiveByteArray(cap), 0)
		{	}

		JHeapByteBuffer::JHeapByteBuffer(JPrimitiveByteArray* buf, jint off, jint len)
			:JByteBuffer(getClazz(), -1, off, off+len, buf->size(),buf,0)
		{	}

		JHeapByteBuffer::JHeapByteBuffer(JPrimitiveByteArray* buf, jint mark, jint pos, jint lim, jint cap, jint off)
			:JByteBuffer(getClazz(), mark, pos, lim, cap, buf, off)
		{	}

		jint JHeapByteBuffer::ix(jint i)
		{
			return i + offset;
		}

		JByteBuffer* JHeapByteBuffer::compact() {
			JSystem::arraycopy(hb, ix(position()), hb, ix(0), remaining());
			position(remaining());
			limit(capacity());
			discardMark();
			return this;
		}

		jbool JHeapByteBuffer::isDirect()
		{
			return false;
		}

		jbyte JHeapByteBuffer::get()
		{
			return hb->getByte(ix(nextGetIndex()));
		}

		jbyte JHeapByteBuffer::get(jint i)
		{
			return hb->getByte(ix(checkIndex(i)));
		}

		JByteBuffer* JHeapByteBuffer::get(JPrimitiveByteArray* dst, jint offset, jint length)
		{
			checkBounds(offset, length, dst->size());
			if (length > remaining())
				throw new JBufferUnderflowException();
			for (int i=offset; i < offset+length; i++){
				dst->setByte(i, this->get());
			}
			return this;
		}

		JByteBuffer* JHeapByteBuffer::put(jbyte x)
		{
			hb->setByte(nextPutIndex(), x);
			return this;
		}

		JByteBuffer* JHeapByteBuffer::put(jint i, jbyte x)
		{
			hb->setByte(ix(checkIndex(i)), x);
			return this;
		}

		JByteBuffer* JHeapByteBuffer::put(JPrimitiveByteArray* src, jint offset, jint length)
		{
			checkBounds(offset, length, src->size());
			if (length > remaining())
				throw new JBufferOverflowException();
			for (int i=offset; i < offset+length; i++){
				this->put(src->getByte(i));
			}
			return this;
		}

		JByteBuffer* JHeapByteBuffer::put(JByteBuffer* src)
		{
			if (src->isInstanceOf(JHeapByteBuffer::getClazz())){
				if (src==this)
					throw new JIllegalArgumentException();
				JHeapByteBuffer* sb = reinterpret_cast<JHeapByteBuffer*>(src);
				int n = sb->remaining();
				if (n > remaining())
					throw new JBufferOverflowException();
				JSystem::arraycopy(sb->hb, sb->ix(sb->position()), hb, ix(position()), n);
				sb->position(position()+n);
				position(position()+n);
			} else if (src->isDirect()){
				jint n = src->remaining();
				if (n > remaining())
					throw new JBufferOverflowException();
				src->get(hb, ix(position()), n);
				position(position() + n);
			}else{
				JByteBuffer::put(src);
			}
			return this;
		}

		jchar JHeapByteBuffer::getChar()
		{
			return JBits::getChar(hb, ix(nextGetIndex(2)), bigEndian);
		}

		jchar JHeapByteBuffer::getChar(jint i)
		{
			return JBits::getChar(hb, ix(checkIndex(i, 2)), bigEndian);
		}

		JByteBuffer* JHeapByteBuffer::putChar(jchar x)
		{
			JBits::putChar(hb, ix(nextPutIndex(2)), x, bigEndian);
			return this;
		}

		JByteBuffer* JHeapByteBuffer::putChar(jint i, jchar x)
		{
			JBits::putChar(hb, ix(checkIndex(i, 2)), x, bigEndian);
			return this;
		}

		JCharBuffer* JHeapByteBuffer::asCharBuffer()
		{
			jint size = this->remaining() >> 1;
			jint off = offset + position();
			return ( bigEndian? (JCharBuffer*)(new JByteBufferAsCharBufferB(this, -1, 0, size, size, off))
					: (JCharBuffer*)(new JByteBufferAsCharBufferL(this, -1, 0, size, size, off))
					);
		}

		JHeapByteBuffer::~JHeapByteBuffer()
		{	}

	}
}








