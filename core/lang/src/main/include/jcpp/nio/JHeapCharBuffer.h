#ifndef JCPP_NIO_JHEAPCHARBUFFER_H
#define JCPP_NIO_JHEAPCHARBUFFER_H

#include "jcpp/lang/JSystem.h"
#include "jcpp/native/api/NativeInclude.h"
#include "jcpp/lang/JPrimitiveCharArray.h"
#include "jcpp/nio/JCharBuffer.h"
#include "jcpp/lang/JStringIndexOutOfBoundsException.h"

namespace jcpp {
	namespace nio {

	// @Class(canonicalName="java.nio.HeapCharBuffer", simpleName="HeapCharBuffer");
	class JCPP_EXPORT JHeapCharBuffer : public JCharBuffer {
	protected:

		jint ix(jint i);

	public:
		JHeapCharBuffer(jint cap, jint lim);
		JHeapCharBuffer(JPrimitiveCharArray* buf, jint off, jint len);
		JHeapCharBuffer(JPrimitiveCharArray* buf, jint mark, jint pos, jint lim, jint cap, jint off);

		static jcpp::lang::JClass* getClazz();

		virtual jchar get();
		virtual jchar get(jint i);
		virtual JCharBuffer* get(JPrimitiveCharArray* dst, jint offset, jint length);
		virtual jbool isDirect();

		virtual JCharBuffer* put(jchar x);
		virtual JCharBuffer* put(jint i, jchar x);
		virtual JCharBuffer* put(JPrimitiveCharArray* src, jint offset, jint length);
		virtual JCharBuffer* put(JCharBuffer* src);

		virtual JCharBuffer* slice();

		virtual JString* toString(jint start, jint end);
		virtual JCharBuffer* subSequence(jint start, jint end);
		virtual JByteOrder* order();

		virtual ~JHeapCharBuffer();

	};

	}
}

#endif /* JHEAPCHARBUFFER_H_ */
