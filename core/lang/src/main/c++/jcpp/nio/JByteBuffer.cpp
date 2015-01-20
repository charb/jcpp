#include "jcpp/nio/JByteBuffer.h"
#include "jcpp/nio/JHeapByteBuffer.h"


namespace jcpp {
	namespace nio {

		JByteBuffer::JByteBuffer(jcpp::lang::JClass* _class, jint mark, jint pos, jint lim, jint cap, JPrimitiveByteArray* hb, jint offset)
			:JBuffer(_class, mark, pos, lim, cap)
		{
			this->hb = hb;
			this->offset = offset;
			nativeByteOrder = (bigEndian == NativeEndian::isBigEndian());
			bigEndian = true;
		}

		JByteBuffer* JByteBuffer::allocate(jint capacity)
		{
			if (capacity < 0)
				throw new JIllegalArgumentException();
			return reinterpret_cast<JByteBuffer*>(new JHeapByteBuffer(capacity, capacity));
		}

		JByteBuffer* JByteBuffer::wrap(JPrimitiveByteArray* array, jint offset, jint length)
		{
			try {
				return reinterpret_cast<JByteBuffer*>(new JHeapByteBuffer(array, offset, length));
			} catch (JIllegalArgumentException* x){
				throw new JIndexOutOfBoundsException();
			}
		}

		JByteBuffer* JByteBuffer::wrap(JPrimitiveByteArray* array)
		{
			return wrap(array, 0, array->size());
		}

		JByteBuffer* JByteBuffer::get(JPrimitiveByteArray* dst, jint offset, jint length)
		{
			checkBounds(offset, length, dst->size());
			if (length > remaining())
				throw new JBufferUnderflowException();
			jint end = offset + length;
			for (jint i = offset; i < end; i++)
				dst->setByte(i, get());
			return this;
		}

		JByteBuffer* JByteBuffer::get(JPrimitiveByteArray* dst)
		{
			return get(dst, 0, dst->size());
		}

		JByteBuffer* JByteBuffer::put(JByteBuffer* src)
		{
			if (src == this)
				throw new JIllegalArgumentException();
			jint n = src->remaining();
			if ( n > remaining())
				throw new JBufferOverflowException();
			for (jint i = 0; i < n; i++)
				put(src->get());
			return this;
		}

		JByteBuffer* JByteBuffer::put(JPrimitiveByteArray* src, jint offset, jint length)
		{
			checkBounds(offset, length, src->size());
			if (length > remaining())
				throw new JBufferOverflowException();
			jint end = offset + length;
			for (jint i = offset; i < end; i++)
				this->put(src->getByte(i));
			return this;
		}

		JByteBuffer* JByteBuffer::put(JPrimitiveByteArray* src)
		{
			return put(src, 0, src->size());
		}

		jbool JByteBuffer::hasArray()
		{
			return (hb != null);
		}

		JObject* JByteBuffer::array()
		{
			return hb;
		}

		jint JByteBuffer::arrayOffset()
		{
			if (hb == null)
				throw new JUnsupportedOperationException();
			return offset;
		}

		JString* JByteBuffer::toString()
		{
			JStringBuilder* sb = new JStringBuilder();
			sb->append(getClass()->getName());
			sb->append("[pos=");
			sb->append(position());
			sb->append(" lim=");
			sb->append(limit());
			sb->append(" cap=");
			sb->append(capacity());
			sb->append("]");
			return sb->toString();
		}

		jint JByteBuffer::hashCode()
		{
			jint h = 1;
			jint p = position();
			for (jint i = limit() - 1; i >= p; i--)
				h = 31*h + (int)get(i);
			return h;
		}

		jbool JByteBuffer::equals(JObject* ob)
		{
			if (this == ob)
				return true;
			if (ob==null)
				return false;
			if (!ob->isInstanceOf(JByteBuffer::getClazz()))
				return false;
			JByteBuffer* that = reinterpret_cast<JByteBuffer*>(ob);
			if (this->remaining() != that->remaining())
				return false;
			jint p = this->position();

			for (jint i = this->limit() -1, j = that->limit() -1; i >= p; i--, j--)
				if (!equals(this->get(i), that->get(i)))
					return false;
			return true;
		}

		jbool JByteBuffer::equals(jbyte x, jbyte y){
			return x==y;
		}

		jint JByteBuffer::compareTo(JObject* that)
		{
			if (!that->isInstanceOf(JByteBuffer::getClazz()))
				throw new JIllegalArgumentException(new JString("Argument to JByteBuffer::compareTo must be of type JByteBuffer"));

			JByteBuffer *thatBuf = (JByteBuffer*)that;
			jint n = this->position() + min(this->remaining(), thatBuf->remaining());
			for (jint i = this->position(), j = thatBuf->position(); i < n; i++, j++){
				jint cmp = compare(this->get(i), thatBuf->get(j));
				if (cmp != 0)
					return cmp;
			}
			return this->remaining() - thatBuf->remaining();
		}

		jint JByteBuffer::compare(jbyte x, jbyte y){
			return x - y;
		}

		JByteOrder* JByteBuffer::order()
		{
			return bigEndian ? JByteOrder::JBIG_ENDIAN : JByteOrder::JLITTLE_ENDIAN;
		}

		JByteBuffer* JByteBuffer::order(JByteOrder* bo)
		{
			bigEndian = (bo == JByteOrder::JBIG_ENDIAN);
			nativeByteOrder = (bigEndian == NativeEndian::isBigEndian());
			return this;
		}

		JByteBuffer::~JByteBuffer()
		{	}


	}
}







