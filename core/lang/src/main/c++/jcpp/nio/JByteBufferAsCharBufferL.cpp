#include "jcpp/nio/JByteBufferAsCharBufferL.h"


namespace jcpp {
	namespace nio {

	JByteBufferAsCharBufferL::JByteBufferAsCharBufferL(JByteBuffer* bb)
		: JCharBuffer(getClazz(), -1, 0, bb->remaining()>>1, bb->remaining()>>1), offset(position())
	{
		this->bb = bb;
		jint cap = capacity();
		limit(cap);
		jint pos = position();
		assert(pos <= cap);
	}

	JByteBufferAsCharBufferL::JByteBufferAsCharBufferL(JByteBuffer* bb, jint mark, jint pos, jint lim, jint cap, jint off)
		:	JCharBuffer(getClazz(), mark, pos, lim, cap), offset(off)
	{
		this->bb = bb;
	}

	JCharBuffer* JByteBufferAsCharBufferL::duplicate() {
		return new JByteBufferAsCharBufferL(bb, this->markValue(), this->position(), this->limit(), this->capacity(), offset);
	}

	jint JByteBufferAsCharBufferL::ix(jint i)
	{
		return (i << 1) + offset;
	}

	jchar JByteBufferAsCharBufferL::get()
	{
		return JBits::getChar((JPrimitiveByteArray*)bb->array(), ix(nextGetIndex()), false);
	}

	jchar JByteBufferAsCharBufferL::get(jint i)
	{
		return JBits::getChar((JPrimitiveByteArray*)bb->array(), ix(checkIndex(i)), false);
	}

	JCharBuffer* JByteBufferAsCharBufferL::put(jchar x)
	{
		JBits::putChar((JPrimitiveByteArray*)bb->array(), ix(nextPutIndex()), x, false);
		return this;
	}

	JCharBuffer* JByteBufferAsCharBufferL::put(jint i, jchar x)
	{
		JBits::putChar((JPrimitiveByteArray*)bb->array(), ix(checkIndex(i)), x, false);
		return this;
	}

	jbool JByteBufferAsCharBufferL::isDirect(){
		//TODO
		return false;
	}

	jbool JByteBufferAsCharBufferL::isReadOnly()
	{
		return false;
	}

	JCharBuffer* JByteBufferAsCharBufferL::slice() {
		jint pos = this->position();
		jint lim = this->limit();
		assert(pos <= lim);
		jint rem = (pos <= lim ? lim-pos : 0);
		jint off = (pos <<1 ) + offset;
		assert(off >= 0);
		return new JByteBufferAsCharBufferL(bb, -1, 0, rem, rem, off);
	}

	JString* JByteBufferAsCharBufferL::toString(jint start, jint end)
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
		} catch(JStringIndexOutOfBoundsException* x){
			throw new JIndexOutOfBoundsException();
		}
	}

	JCharBuffer* JByteBufferAsCharBufferL::subSequence(jint start, jint end)
	{
		jint pos = position();
		jint lim  = limit();
		assert(pos <= lim);
		pos = (pos <= lim)? pos : lim;
		jint len = lim - pos;

		if ((start < 0) || (end > len) || (start > end))
			throw new JIndexOutOfBoundsException();
		return new JByteBufferAsCharBufferL(bb, -1, pos+start, pos+end, capacity(), offset);
	}

	JByteOrder* JByteBufferAsCharBufferL::order(){
		return const_cast<JByteOrder*>(JByteOrder::JLITTLE_ENDIAN);
	}

	JByteBufferAsCharBufferL::~JByteBufferAsCharBufferL()
	{	}


	}
}

