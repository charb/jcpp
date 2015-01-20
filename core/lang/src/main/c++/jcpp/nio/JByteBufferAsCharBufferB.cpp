#include "jcpp/nio/JByteBufferAsCharBufferB.h"


namespace jcpp {
	namespace nio {

	JByteBufferAsCharBufferB::JByteBufferAsCharBufferB(JByteBuffer* bb)
		: JCharBuffer(getClazz(), -1, 0, bb->remaining()>>1, bb->remaining()>>1) , offset(this->capacity())
	{
		this->bb = bb;
		jint cap = this->capacity();
		this->limit(cap);
		jint pos = this->position();
		assert(pos <= cap);
	}

	JByteBufferAsCharBufferB::JByteBufferAsCharBufferB(JByteBuffer* bb, jint mark, jint pos, jint lim, jint cap, jint off)
		: JCharBuffer(getClazz(), mark, pos, lim, cap), offset(off)
	{
		this->bb = bb;
	}

	JByteBufferAsCharBufferB::~JByteBufferAsCharBufferB()
	{	}

	JCharBuffer* JByteBufferAsCharBufferB::duplicate()
	{
		return new JByteBufferAsCharBufferB(bb, this->markValue(), this->position(), this->limit(), this->capacity(), offset);
	}

	jint JByteBufferAsCharBufferB::ix(jint i)
	{
		return (i << 1) + offset;
	}

	jchar JByteBufferAsCharBufferB::get()
	{
		return JBits::getChar((JPrimitiveByteArray*)bb->array(), ix(nextGetIndex()), true);
	}

	jchar JByteBufferAsCharBufferB::get(jint i)
	{
		return JBits::getChar((JPrimitiveByteArray*)bb->array(), ix(checkIndex(i)), true);
	}

	JCharBuffer* JByteBufferAsCharBufferB::put(jchar x)
	{
		JBits::putChar((JPrimitiveByteArray*)bb->array(), ix(nextPutIndex()), x, true);
		return this;
	}

	JCharBuffer* JByteBufferAsCharBufferB::put(jint i, jchar x)
	{
		JBits::putChar((JPrimitiveByteArray*)bb->array(), ix(checkIndex(i)), x, true);
		return this;
	}

	jbool JByteBufferAsCharBufferB::isDirect(){
		//TODO
		return false;
	}

	jbool JByteBufferAsCharBufferB::isReadOnly()
	{
		return false;
	}

	JCharBuffer* JByteBufferAsCharBufferB::slice() {
		jint pos = this->position();
		jint lim = this->limit();
		assert(pos <= lim);
		jint rem = (pos <= lim ? lim - pos : 0);
		jint off = (pos << 1) + offset;
		assert(off >= 0);
		return new JByteBufferAsCharBufferB(bb, -1, 0, rem, rem, off);
	}

	JString* JByteBufferAsCharBufferB::toString(jint start, jint end)
	{
		if ((end > limit()) || (start > end))
			throw new JIndexOutOfBoundsException();
		try {
			jint len = end - start;
			JPrimitiveCharArray* ca = new JPrimitiveCharArray(len);
			JCharBuffer* cb = JCharBuffer::wrap(ca);
			JCharBuffer* db = this->duplicate();
			db->position(start);
			db->limit(end);
			cb->put(db);
			return new JString(ca);
		}catch (JStringIndexOutOfBoundsException* x){
			throw new JIndexOutOfBoundsException();
		}
	}

	JCharBuffer* JByteBufferAsCharBufferB::subSequence(jint start, jint end)
	{
		jint pos = position();
		jint lim = limit();
		assert(pos <= lim);
		pos = (pos <= lim? pos : lim);
		jint len = lim - pos;

		if ((start < 0) || (end > len) || (start > end))
			throw new JIndexOutOfBoundsException();
		return new JByteBufferAsCharBufferB(bb, -1, pos+start, pos+end, capacity(), offset);
	}

	JByteOrder* JByteBufferAsCharBufferB::order()
	{
		return JByteOrder::JBIG_ENDIAN;
	}


	}
}
