#ifndef JCPP_NIO_JSTRINGCHARBUFFER_H
#define JCPP_NIO_JSTRINGCHARBUFFER_H

#include "jcpp/native/api/NativeEndian.h"
#include "jcpp/native/api/NativeInclude.h"
#include "jcpp/lang/JString.h"
#include "jcpp/lang/JIndexOutOfBoundsException.h"
#include "jcpp/nio/JReadOnlyBufferException.h"
#include "jcpp/nio/JCharBuffer.h"

namespace jcpp {
	namespace nio {

	// @Class(canonicalName="java.nio.StringCharBuffer", simpleName="StringCharBuffer");
	class JCPP_EXPORT JStringCharBuffer : public JCharBuffer{
	protected:
		JCharSequence* str;

	private:
		JStringCharBuffer(JCharSequence* s, jint mark, jint pos, jint limit, jint cap, jint offset);

	public:
		JStringCharBuffer(JCharSequence* s, jint start, jint end);

		static jcpp::lang::JClass* getClazz();

		virtual jchar get();
		virtual jchar get(jint index);
		virtual JCharBuffer* put(jchar c);
		virtual JCharBuffer* put(jint index, jchar c);
		jbool isReadOnly();
		virtual JCharBuffer* slice();
		virtual JString* toString(jint start, jint end);
		virtual JCharBuffer* subSequence(jint start, jint end);
		virtual jbool isDirect();
		virtual JByteOrder* order();

		virtual ~JStringCharBuffer();
	};




	}
}



#endif /* JSTRINGCHARBUFFER_H_ */
