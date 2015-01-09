#ifndef JCPP_NIO_CS_JHISTORICALLYNAMEDCHARSET_H
#define JCPP_NIO_CS_JHISTORICALLYNAMEDCHARSET_H

#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JString.h"

using namespace jcpp::lang;

namespace jcpp {
	namespace nio {
		namespace cs {

	// @Class(canonicalName="sun.nio.cs.HistoricallyNamedCharset", simpleName="HistoricallyNamedCharset");
	class JCPP_EXPORT JHistoricallyNamedCharset : public JInterface {
	public:
		~JHistoricallyNamedCharset();

		virtual JString* historicalName() = 0;

		static jcpp::lang::JClass* getClazz();

	};


		}
	}
}


#endif /* JHISTORICALLYNAMEDCHARSET_H_ */
