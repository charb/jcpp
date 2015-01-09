#include "jcpp/nio/JCharBuffer.h"
#include "jcpp/nio/JHeapCharBuffer.h"
#include "jcpp/nio/JStringCharBuffer.h"


namespace jcpp {
	namespace nio {

	JCharBuffer::JCharBuffer(jcpp::lang::JClass* _class, jint mark, jint pos, jint lim, jint cap, JPrimitiveCharArray* hb, jint offset)
		: JBuffer(_class, mark, pos, lim, cap), isReadOnly(false)
	{
		this->hb = hb;
		this->offset = offset;
	}


	JCharBuffer* JCharBuffer::allocate(jint capacity)
	{
		if (capacity < 0)
			throw new JIllegalArgumentException();
		return reinterpret_cast<JCharBuffer*>(new JHeapCharBuffer(capacity, capacity));
	}

	JCharBuffer* JCharBuffer::wrap(JPrimitiveCharArray* array, jint offset, jint length)
	{
		try{
			return reinterpret_cast<JCharBuffer*>(new JHeapCharBuffer(array, offset, length));
		} catch(JIllegalArgumentException* x){
			throw new JIndexOutOfBoundsException();
		}
	}

	JCharBuffer* JCharBuffer::wrap(JPrimitiveCharArray* array)
	{
		return wrap(array, 0, array->size());
	}

	jint JCharBuffer::read(JCharBuffer* target)
	{
		jint targetRemaining = target->remaining();
		jint _remaining = remaining();
		if (_remaining == 0)
			return -1;
		jint n = min(_remaining, targetRemaining);
		jint _limit = limit();
		if (targetRemaining < _remaining)
			limit(position() + n);
		try {
			if (n > 0)
				target->put(this);
		}catch(JThrowable* e){
			this->limit(_limit);
		}
		this->limit(_limit);
		return n;
	}

	JCharBuffer* JCharBuffer::wrap(JCharSequence* csq, jint start, jint end)
	{
		try{
			return reinterpret_cast<JCharBuffer*>(new JStringCharBuffer(csq, start, end));
		} catch(JIllegalArgumentException* x){
			throw new JIndexOutOfBoundsException();
		}
	}

	JCharBuffer* JCharBuffer::wrap(JCharSequence* csq)
	{
		return wrap(csq, 0, csq->length());
	}

	JCharBuffer* JCharBuffer::get(JPrimitiveCharArray* dst, jint offset, jint length)
	{
		checkBounds(offset, length, dst->size());
		if (length > remaining())
			throw new JBufferUnderflowException();
		jint end = offset + length;
		for (jint i = offset; i < end; i++)
			dst->setChar(i, get());
		return this;
	}

	JCharBuffer* JCharBuffer::get(JPrimitiveCharArray* dst)
	{
		return get(dst, 0, dst->size());
	}

	JCharBuffer* JCharBuffer::put(JCharBuffer* src)
	{
		if (src == this)
			throw new JIllegalArgumentException();
		int n = src->remaining();
		if (n > remaining())
			throw new JBufferOverflowException();
		for (jint i = 0; i < n; i++)
			put(src->get());
		return this;
	}

	JCharBuffer* JCharBuffer::put(JPrimitiveCharArray* src, jint offset, jint length)
	{
		checkBounds(offset, length, src->size());
		if (length > remaining())
			throw new JBufferOverflowException();
		jint end = offset + length;
		for (jint i = offset; i < end; i++)
			this->put(src->getChar(i));
		return this;
	}

	JCharBuffer* JCharBuffer::put(JPrimitiveCharArray* src)
	{
		return put(src, 0, src->size());
	}

	JCharBuffer* JCharBuffer::put(JString* src, jint start, jint end)
	{
		checkBounds(start, end-start, src->length());
		for (jint i = start; i < end; i++)
			this->put(src->charAt(i));
		return this;
	}

	JCharBuffer* JCharBuffer::put(JString* src)
	{
		return put(src, 0, src->length());
	}

	jbool JCharBuffer::hasArray()
	{
		return (hb != null);
	}

	JObject* JCharBuffer::array()
	{
		if (hb == null)
			throw new JUnsupportedOperationException();
		return hb;
	}

	jint JCharBuffer::arrayOffset()
	{
		if (hb == null)
			throw new JUnsupportedOperationException();
		return offset;
	}

	jint JCharBuffer::hashCode()
	{
		jint h = 1;
		jint p = position();
		for (jint i = limit() - 1; i >= p; i--)
			h = 31*h + (jint)get(i);
		return h;
	}

	jbool JCharBuffer::equals(JObject* ob)
	{
		if (this == ob)
			return true;
		if (ob == null)
			return false;
		if (!ob->isInstanceOf(JCharBuffer::getClazz()))
			return false;
		JCharBuffer* that = (JCharBuffer*)ob;
		if (this->remaining() != that->remaining())
			return false;
		jint p = this->position();

		for (jint i = this->limit() -1, j = that->limit() - 1; i >= p; i--, j--)
			if (!equals(this->get(i), that->get(j)))
				return false;
		return true;
	}

	jbool JCharBuffer::equals(jchar x, jchar y)
	{
		return x == y;
	}

	jint JCharBuffer::compareTo(JObject* that)
	{
		JCharBuffer* thatBuf = (JCharBuffer*)that;
		jint n = this->position() + min(this->remaining(), thatBuf->remaining());

		for (jint i = this->position(), j = thatBuf->position(); i < n; i++, j++){
			jint cmp = compare(this->get(i), thatBuf->get(j));
			if (cmp != 0)
				return cmp;
		}
		return this->remaining() - thatBuf->remaining();
	}

	jint JCharBuffer::compare(jchar x, jchar y)
	{
		return JCharacter::compare(x, y);
	}

	JString* JCharBuffer::toString()
	{
		return toString(position(), limit());
	}

	jint JCharBuffer::length()
	{
		return remaining();
	}

	jchar JCharBuffer::charAt(jint index)
	{
		return get(position() + checkIndex(index, 1));
	}

	JCharBuffer* JCharBuffer::append(JCharSequence* csq)
	{
		if (csq == null)
			return put(new JString("null"));
		else
			return put(csq->toString());
	}

	JCharBuffer* JCharBuffer::append(JCharSequence* csq, jint start, jint end)
	{
		if (csq!=null)
			return put(csq->subSequence(start,end)->toString());
		else
			return put(new JString("null"));
	}

	JCharBuffer* JCharBuffer::append(jchar c)
	{
		return put(c);
	}

	JCharBuffer::~JCharBuffer()
	{	}





	}
}


