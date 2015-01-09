#ifndef JCPP_NIO_CS_JARRAYENCODER_H
#define JCPP_NIO_CS_JARRAYENCODER_H

#include "jcpp/native/api/NativeInclude.h"
#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JPrimitiveCharArray.h"
#include "jcpp/lang/JPrimitiveByteArray.h"

using namespace jcpp::lang;

namespace jcpp {
	namespace nio {
		namespace cs {

	// @Class(canonicalName="sun.nio.cs.ArrayEncoder", simpleName="ArrayEncoder");
	class JCPP_EXPORT JArrayEncoder : public JInterface {
	public:
		virtual ~JArrayEncoder();

		virtual jint encode(JPrimitiveCharArray* src, jint off, jint len, JPrimitiveByteArray* dst) = 0;

		static jcpp::lang::JClass* getClazz();
	};


		}
	}
}


#endif /* JARRAYENCODER_H_ */
