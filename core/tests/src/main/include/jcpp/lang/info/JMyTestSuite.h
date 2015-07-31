#ifndef JCPP_INFO_MY_TEST_SUITE_H_
#define JCPP_INFO_MY_TEST_SUITE_H_

#include "junit/framework/JTestSuite.h"

using namespace junit::framework;

namespace jcpp{
	namespace lang{
		namespace info{
			//@Class(canonicalName="jcpp.lang.info.MyTestSuite", simpleName="MyTestSuite");
			class JCPP_EXPORT JMyTestSuite : public JTestSuite{
			public:

				JMyTestSuite();

				static JClass *getClazz();

				virtual ~JMyTestSuite();
			};
		}
	}
}


#endif
