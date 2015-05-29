#ifndef JCPP_INFO_TEST_SUITE_H_
#define JCPP_INFO_TEST_SUITE_H_

#include "jcpp/lang/JString.h"
#include "junit/framework/JTestSuite.h"

using namespace junit::framework;

namespace jcpp {
	namespace lang {
		namespace info {
			//@Class(canonicalName="jcpp.lang.info.infoTestSuite", simpleName="infoTestSuite");
			class JCPP_EXPORT JInfoTestSuite : public JTestSuite {
				public:
				JInfoTestSuite();

					static JClass* getClazz();

					virtual ~JInfoTestSuite();

			};
		}
	}
}
#endif
