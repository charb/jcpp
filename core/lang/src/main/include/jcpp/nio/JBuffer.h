#ifndef JCPP_NIO_JBUFFER_H
#define JCPP_NIO_JBUFFER_H

#include "jcpp/lang/JObject.h"
#include "jcpp/native/api/NativeInclude.h"
#include "jcpp/nio/JInvalidMarkException.h"
#include "jcpp/lang/JIllegalArgumentException.h"
#include "jcpp/lang/JIndexOutOfBoundsException.h"
#include "jcpp/nio/JBufferOverflowException.h"
#include "jcpp/nio/JBufferUnderflowException.h"
#include "jcpp/lang/JStringBuilder.h"

namespace jcpp {
	namespace nio {

	// @Class(canonicalName="java.nio.Buffer", simpleName="Buffer");
	class JCPP_EXPORT JBuffer : public JObject {
	private:
		jint _mark;
		jint _position;
		jint _limit;
		jint _capacity;

		jlong address;

	protected:
		JBuffer(jcpp::lang::JClass* _class, jint mark, jint pos, jint lim, jint cap);
		static void checkBounds(jint off, jint len, jint size);

	public:
		virtual ~JBuffer();
		static jcpp::lang::JClass* getClazz();

		jint capacity();
		jint position();
		JBuffer* position(jint newPosition);
		jint limit();
		JBuffer* limit(jint newLimit);
		JBuffer* mark();
		JBuffer* reset();
		JBuffer* clear();
		JBuffer* flip();
		JBuffer* rewind();
		jint remaining();
		jbool hasRemaining();
		virtual jbool hasArray() = 0;
		virtual jbool isDirect() = 0;
		virtual JObject* array() = 0;
		virtual jint arrayOffset() = 0;
		jint nextGetIndex();
		jint nextGetIndex(jint nb);
		jint nextPutIndex();
		jint nextPutIndex(jint nb);
		jint checkIndex(jint i);
		jint checkIndex(jint i, jint nb);
		jint markValue();
		void truncate();
		void discardMark();

	};

	}
}



#endif /* JBUFFER_H_ */
