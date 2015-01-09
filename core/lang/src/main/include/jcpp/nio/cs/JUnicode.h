#ifndef JCPP_NIO_CS_JUNICODE_H
#define JCPP_NIO_CS_JUNICODE_H

#include "jcpp/nio/charset/JCharset.h"
#include "jcpp/nio/cs/JHistoricallyNamedCharset.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"

using namespace jcpp::nio::charset;

namespace jcpp {
	namespace nio {
		namespace cs {

	// @Class(canonicalName="sun.nio.cs.Unicode", simpleName="Unicode");
	class JCPP_EXPORT JUnicode : public JCharset, public JHistoricallyNamedCharset {
	public:
		JUnicode(jcpp::lang::JClass* _class, JString* name, JPrimitiveObjectArray* aliases);

		jbool contains(JCharset* cs);

		static jcpp::lang::JClass* getClazz();

		virtual ~JUnicode();
	};


		}
	}
}


#endif /* JUNICODE_H_ */
