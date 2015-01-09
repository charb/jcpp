#ifndef JCPP_UTIL_CONCURRENT_LOCKS_TEST_SUITE_H
#define JCPP_UTIL_CONCURRENT_LOCKS_TEST_SUITE_H

#include "jcpp/lang/JString.h"
#include "junit/framework/JTestSuite.h"

using namespace junit::framework;

namespace jcpp{
	namespace util{
		namespace concurrent{
			namespace locks{

				// @Class(canonicalName="jcpp.util.concurrent.locks.LocksTestSuite", simpleName="LocksTestSuite");
			    class JCPP_EXPORT JLocksTestSuite : public JTestSuite{
			    public:
			        JLocksTestSuite();

			        static JClass* getClazz();

			        virtual ~JLocksTestSuite();
			    };
			}
		}
	}
}
#endif
