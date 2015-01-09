#ifndef JCPP_NIO_CHARSET_JCODINGERRORACTION_H
#define JCPP_NIO_CHARSET_JCODINGERRORACTION_H

#include "jcpp/lang/JClass.h"
#include "jcpp/native/api/NativeInclude.h"
#include "jcpp/lang/JString.h"

namespace jcpp {
	namespace nio {
		namespace charset {

	// @Class(canonicalName="java.nio.charset.CodingErrorAction", simpleName="CodingErrorAction");
	class JCPP_EXPORT JCodingErrorAction : public JObject {
	private:
		JString* name;
		JCodingErrorAction(JString* name);

	public:
		static const JCodingErrorAction* IGNORE;
		static const JCodingErrorAction* REPLACE;
		static const JCodingErrorAction* REPORT;

		static jcpp::lang::JClass* getClazz();

		virtual JString* toString();

		virtual ~JCodingErrorAction();
	};

		}
	}
}


#endif
