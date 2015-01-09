#ifndef JCPP_IO_JHEAPBYTEBUFFER_H
#define JCPP_IO_JHEAPBYTEBUFFER_H

#include "jcpp/lang/JSystem.h"
#include "jcpp/lang/JString.h"
#include "jcpp/native/api/NativeInclude.h"
#include "jcpp/nio/JByteBuffer.h"
#include "jcpp/io/JBits.h"
#include "jcpp/nio/JCharBuffer.h"
#include "jcpp/nio/JByteBufferAsCharBufferB.h"
#include "jcpp/nio/JByteBufferAsCharBufferL.h"

namespace jcpp {
	namespace nio {

	// @Class(canonicalName="java.nio.charset.HeapByteBuffer", simpleName="HeapByteBuffer");
	class JCPP_EXPORT JHeapByteBuffer : public JByteBuffer {
	protected:

		jint ix(jint i);

	public:
		JHeapByteBuffer(jint cap, jint lim);
		JHeapByteBuffer(JPrimitiveByteArray* buf, jint off, jint len);
		JHeapByteBuffer(JPrimitiveByteArray* buf, jint mark, jint pos, jint lim, jint cap, jint off);

		static jcpp::lang::JClass* getClazz();

		virtual JByteBuffer* compact();
		virtual jbool isDirect();
		virtual jbyte get();
		virtual jbyte get(jint i);
		virtual JByteBuffer* get(JPrimitiveByteArray* dst, jint offset, jint length);
		virtual JByteBuffer* put(jbyte x);
		virtual JByteBuffer* put(jint i, jbyte x);
		virtual JByteBuffer* put(JPrimitiveByteArray* src, jint offset, jint length);
		virtual JByteBuffer* put(JByteBuffer* src);

		virtual jchar getChar();
		virtual jchar getChar(jint i);
		virtual JByteBuffer* putChar(jchar x);
		virtual JByteBuffer* putChar(jint i, jchar x);
		virtual JCharBuffer* asCharBuffer();

		virtual ~JHeapByteBuffer();
	};


	}
}

#endif /* JHEAPBYTEBUFFER_H_ */

