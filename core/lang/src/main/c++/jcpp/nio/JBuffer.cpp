#include "jcpp/nio/JBuffer.h"


namespace jcpp {
	namespace nio {

	JBuffer::JBuffer(jcpp::lang::JClass* _class, jint mark, jint pos, jint lim, jint cap)
		:	JObject(_class)
	{
		if (cap < 0){
			JStringBuilder* strBuilder = new JStringBuilder(new JString("Negative capacity: "));
			strBuilder->append(cap);
			throw new JIllegalArgumentException(strBuilder->toString());
		}
		_capacity = cap;
		_mark = -1;
		_position = 0;
		limit(lim);
		position(pos);
		if (mark >= 0){
			if (mark > pos) {
				JStringBuilder* msgStrBuilder = new JStringBuilder(new JString("mark > position: ("));
				msgStrBuilder->append(mark);
				msgStrBuilder->append(" > ");
				msgStrBuilder->append(pos);
				msgStrBuilder->append(")");
				throw new JIllegalArgumentException(msgStrBuilder->toString());
			}
			_mark = mark;
		}
	}

	JBuffer::~JBuffer(){}

	jint JBuffer::capacity(){
		return _capacity;
	}

	jint JBuffer::position(){
		return _position;
	}

	JBuffer* JBuffer::position(jint newPosition){
		if ((newPosition > _limit) || (newPosition < 0))
			throw new JIllegalArgumentException();
		_position = newPosition;
		if (_mark > _position) _mark = -1;
		return this;
	}

	jint JBuffer::limit(){
		return _limit;
	}

	JBuffer* JBuffer::limit(jint newLimit){
		if ((newLimit > _capacity) || (newLimit < 0))
			throw new JIllegalArgumentException();
		_limit = newLimit;
		if (_position > _limit) _position = _limit;
		if (_mark > _limit) _mark = -1;
		return this;
	}

	JBuffer* JBuffer::mark(){
		_mark = _position;
		return this;
	}

	JBuffer* JBuffer::reset(){
		jint m = _mark;
		if (m < 0)
			throw new JInvalidMarkException();
		_position = m;
		return this;
	}

	JBuffer* JBuffer::clear(){
		_position = 0;
		_limit = _capacity;
		_mark = -1;
		return this;
	}

	JBuffer* JBuffer::flip(){
		_limit = _position;
		_position = 0;
		_mark = -1;
		return this;
	}

	JBuffer* JBuffer::rewind(){
		_position = 0;
		_mark = -1;
		return this;
	}

	jint JBuffer::remaining(){
		return _limit - _position;
	}

	jbool JBuffer::hasRemaining(){
		return _position < _limit;
	}

	jint JBuffer::nextGetIndex(){
		if (_position >= _limit)
			throw new JBufferUnderflowException();
		return _position++;
	}

	jint JBuffer::nextGetIndex(jint nb){
		if (_limit - _position < nb)
			throw new JBufferUnderflowException();
		jint p = _position;
		_position += nb;
		return p;
	}

	jint JBuffer::nextPutIndex(){
		if (_position >= _limit)
			throw new JBufferOverflowException();
		return _position++;
	}

	jint JBuffer::nextPutIndex(jint nb){
		if (_limit - _position < nb)
			throw new JBufferOverflowException();
		jint p = _position;
		_position += nb;
		return p;
	}

	jint JBuffer::checkIndex(jint i){
		if ((i<0) || (i >= _limit))
			throw new JIndexOutOfBoundsException();
		return i;
	}

	jint JBuffer::checkIndex(jint i, jint nb){
		if ((i < 0) || (nb > _limit -i))
			throw new JIndexOutOfBoundsException();
		return i;
	}

	jint JBuffer::markValue(){
		return _mark;
	}

	void JBuffer::truncate(){
		_mark = -1;
		_position = 0;
		_limit = 0;
		_capacity = 0;
	}

	void JBuffer::discardMark(){
		_mark = -1;
	}

	void JBuffer::checkBounds(jint off, jint len, jint size){
		if ((off | len | (off+len) | (size - (off+len))) < 0)
			throw new JIndexOutOfBoundsException();
	}


	}
}
