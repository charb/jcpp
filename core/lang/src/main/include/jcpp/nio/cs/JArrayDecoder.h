#ifndef JCPP_NIO_CS_JARRAYDECODER_H
#define JCPP_NIO_CS_JARRAYDECODER_H


#include "jcpp/native/api/NativeInclude.h"
#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JPrimitiveCharArray.h"
#include "jcpp/lang/JPrimitiveByteArray.h"


namespace jcpp {
	namespace nio {
		namespace cs {

	// @Class(canonicalName="sun.nio.cs.ArrayDecoder", simpleName="ArrayDecoder");
	class JCPP_EXPORT JArrayDecoder : public JInterface {
	public:
		virtual ~JArrayDecoder();

		virtual jint decode(JPrimitiveByteArray* src, jint off, jint len, JPrimitiveCharArray* dst) = 0;

		static jcpp::lang::JClass* getClazz();
	};

		}
	}
}


#endif /* JARRAYDECODER_H_ */
