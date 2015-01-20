#ifndef JCPP_NIO_JBYTEORDER_H
#define JCPP_NIO_JBYTEORDER_H

#include "jcpp/lang/JClass.h"
#include "jcpp/native/api/NativeInclude.h"
#include "jcpp/native/api/NativeEndian.h"
#include "jcpp/lang/JString.h"

using namespace jcpp::native::api;

namespace jcpp {
	namespace nio {

	// @Class(canonicalName="java.nio.ByteOrder", simpleName="ByteOrder");
	class JCPP_EXPORT JByteOrder : public JObject{
	private:
		JString* name;

		JByteOrder(JString* name);

	public:
		static jcpp::lang::JClass* getClazz();

		static JByteOrder* JBIG_ENDIAN;
		static JByteOrder* JLITTLE_ENDIAN;

		static JByteOrder* nativerOrder();

		virtual JString* toString();

		virtual ~JByteOrder();
	};

	}
}



#endif /* JBYTEORDER_H_ */
