#ifndef JCPP_NIO_JBYTEBUFFER_H
#define JCPP_NIO_JBYTEBUFFER_H

#include "jcpp/nio/JBuffer.h"
#include "jcpp/nio/JByteOrder.h"
#include "jcpp/nio/JCharBuffer.h"
#include "jcpp/lang/JPrimitiveByteArray.h"
#include "jcpp/lang/JUnsupportedOperationException.h"
#include "jcpp/lang/JStringBuffer.h"

namespace jcpp {
	namespace nio {

	// @Class(canonicalName="java.nio.ByteBuffer", simpleName="ByteBuffer");
	class JCPP_EXPORT JByteBuffer : public JBuffer, public JComparable {
	protected:
		JPrimitiveByteArray* hb;
		jint offset;

		jbool bigEndian;
		jbool nativeByteOrder;

		JByteBuffer(jcpp::lang::JClass* _class, jint mark, jint pos, jint lim, jint cap, JPrimitiveByteArray* hb = null, jint off = 0);

	public:
		static jcpp::lang::JClass* getClazz();

		static JByteBuffer* allocate(jint capacity);
		static JByteBuffer* wrap(JPrimitiveByteArray* array, jint offset, jint length);
		static JByteBuffer* wrap(JPrimitiveByteArray* array);

		virtual JByteBuffer* compact() = 0;
		virtual jbool isDirect() = 0;
		virtual jbyte get() = 0;
		virtual JByteBuffer* put(jbyte b) = 0;
		virtual jbyte get(jint index) = 0;
		virtual JByteBuffer* put(jint index, jbyte b) = 0;
		virtual JByteBuffer* get(JPrimitiveByteArray* dst, jint offset, jint length);
		virtual JByteBuffer* get(JPrimitiveByteArray* dst);
		virtual JByteBuffer* put(JByteBuffer* src);
		virtual JByteBuffer* put(JPrimitiveByteArray* src, jint offset, jint length);
		virtual JByteBuffer* put(JPrimitiveByteArray* src);

		virtual jbool hasArray();
		virtual JObject* array();
		virtual jint arrayOffset();
		virtual JString* toString();
		virtual jint hashCode();
		virtual jbool equals(JObject* ob);
		virtual jint compareTo(JObject* that);

		JByteOrder* order();
		JByteBuffer* order(JByteOrder* bo);

		virtual jchar getChar() = 0;
		virtual JByteBuffer* putChar(jchar value) = 0;
		virtual jchar getChar(jint index) = 0;
		virtual JByteBuffer* putChar(jint index, jchar value) = 0;
		virtual JCharBuffer* asCharBuffer() = 0;

		virtual ~JByteBuffer();

	private:
		static jbool equals(jbyte x, jbyte y);
		static jint compare(jbyte x, jbyte y);
	};


	}
}



#endif /* JBYTEBUFFER_H_ */
