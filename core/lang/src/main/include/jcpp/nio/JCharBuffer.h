#ifndef JCPP_NIO_JCHARBUFFER_H
#define JCPP_NIO_JCHARBUFFER_H

#include "jcpp/lang/JClass.h"
#include "jcpp/nio/JBuffer.h"
#include "jcpp/lang/JAppendable.h"
#include "jcpp/lang/JReadable.h"
#include "jcpp/lang/JPrimitiveCharArray.h"
#include "jcpp/nio/JByteOrder.h"
#include "jcpp/lang/JUnsupportedOperationException.h"
#include "jcpp/lang/JCharacter.h"

namespace jcpp {
	namespace nio {

	// @Class(canonicalName="java.nio.CharBuffer", simpleName="CharBuffer");
	class JCPP_EXPORT JCharBuffer : public JBuffer, public JComparable, public JAppendable, public JCharSequence, public JReadable{
	protected:
		JPrimitiveCharArray* hb;
		jint offset;
		jbool isReadOnly;

		JCharBuffer(jcpp::lang::JClass* _class, jint mark, jint pos, jint lim, jint cap, JPrimitiveCharArray* hb = null, jint offset = 0);

	public:
		static jcpp::lang::JClass* getClazz();

		static JCharBuffer* allocate(jint capacity);
		static JCharBuffer* wrap(JPrimitiveCharArray* array, jint offset, jint length);
		static JCharBuffer* wrap(JPrimitiveCharArray* array);
		jint read(JCharBuffer* target);
		static JCharBuffer* wrap(JCharSequence* csq, jint start, jint end);
		static JCharBuffer* wrap(JCharSequence* csq);
		virtual JCharBuffer* slice() = 0;

		virtual jchar get() = 0;
		virtual jchar get(jint index) = 0;
		JCharBuffer* get(JPrimitiveCharArray* dst, jint offset, jint length);
		JCharBuffer* get(JPrimitiveCharArray* dst);

		virtual JCharBuffer* put(jchar c) = 0;
		virtual JCharBuffer* put(jint index, jchar c) = 0;
		JCharBuffer* put(JCharBuffer* src);
		JCharBuffer* put(JPrimitiveCharArray* src, jint offset, jint length);
		JCharBuffer* put(JPrimitiveCharArray* src);
		JCharBuffer* put(JString* src, jint start, jint end);
		JCharBuffer* put(JString* src);

		virtual jbool hasArray();
		virtual JObject* array();
		virtual jint arrayOffset();
		virtual jbool isDirect() = 0;
		virtual jint hashCode();
		virtual jbool equals(JObject* ob);
		static jbool equals(jchar x, jchar y);
		virtual jint compareTo(JObject *that);
		static jint compare(jchar x, jchar y);
		virtual JString* toString();
		virtual JString* toString(jint start, jint end) = 0;
		virtual jint length();
		virtual jchar charAt(jint index);
		//FIXME virtual JCharBuffer* subSequence(jint start, jint end) = 0;
		virtual JCharBuffer* append(JCharSequence* csq);
		virtual JCharBuffer* append(JCharSequence* csq, jint start, jint end);
		virtual JCharBuffer* append(jchar c);
		virtual JByteOrder* order() = 0;

		virtual ~JCharBuffer();
	};

	}
}



#endif /* JCHARBUFFER_H_ */
