#ifndef JCPP_UTIL_CONCURRENT_TEST_SUITE_H
#define JCPP_UTIL_CONCURRENT_TEST_SUITE_H

#include "jcpp/lang/JString.h"
#include "junit/framework/JTestSuite.h"

using namespace junit::framework;

namespace jcpp{
	namespace util{
		namespace concurrent{

			// @Class(canonicalName="jcpp.util.concurrent.ConcurrentTestSuite", simpleName="ConcurrentTestSuite");
		    class JCPP_EXPORT JConcurrentTestSuite : public JTestSuite{
		    public:
		        JConcurrentTestSuite();

		        static JClass* getClazz();

		        static JConcurrentTestSuite* suite();

		        virtual ~JConcurrentTestSuite();
		    };
		}
	}
}
#endif
