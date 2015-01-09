#include "jcpp/nio/JStringCharBuffer.h"


namespace jcpp {
	namespace nio {

	JStringCharBuffer::JStringCharBuffer(JCharSequence* s, jint start, jint end)
		: JCharBuffer(getClazz(), -1, start, end, s->length())
	{
		jint n = s->length();
		if ((start < 0) || (start > n) || (end < start) || (end > n))
			throw new JIndexOutOfBoundsException();
		str = s;
	}

	JStringCharBuffer::JStringCharBuffer(JCharSequence* s, jint mark, jint pos, jint limit, jint cap, jint offset)
		: JCharBuffer(getClazz(), mark, pos, limit, cap, null, offset)
	{
		str = s;
	}

	jchar JStringCharBuffer::get()
	{
		return str->charAt(nextGetIndex() + offset);
	}

	jchar JStringCharBuffer::get(jint index)
	{
		return str->charAt(checkIndex(index) + offset);
	}

	JCharBuffer* JStringCharBuffer::put(jchar c)
	{
		throw new JReadOnlyBufferException();
	}

	JCharBuffer* JStringCharBuffer::put(jint index, jchar c)
	{
		throw new JReadOnlyBufferException();
	}

	jbool JStringCharBuffer::isReadOnly()
	{
		return true;
	}

	JCharBuffer* JStringCharBuffer::slice() {
		return new JStringCharBuffer(str, -1, 0, this->remaining(), this->remaining(), this->position() + offset);
	}

	JString* JStringCharBuffer::toString(jint start, jint end)
	{
		return str->toString()->substring(start + offset, end + offset);
	}

	JCharBuffer* JStringCharBuffer::subSequence(jint start, jint end)
	{
		try{
			jint pos = position();
			return new JStringCharBuffer(str, -1, pos+checkIndex(start, pos),
					pos+checkIndex(end, pos), capacity(), offset);
		} catch (JIllegalArgumentException* x){
			throw new JIndexOutOfBoundsException();
		}
	}

	jbool JStringCharBuffer::isDirect()
	{
		return false;
	}

	JByteOrder* JStringCharBuffer::order()
	{
		if (NativeEndian::isBigEndian()){
			return const_cast<JByteOrder*>(JByteOrder::JBIG_ENDIAN);
		}else{
			return const_cast<JByteOrder*>(JByteOrder::JLITTLE_ENDIAN);
		}
	}

	JStringCharBuffer::~JStringCharBuffer()
	{	}


	}
}
