#ifndef JCPP_UTIL_CONCURRENT_LOCKS_JEXECUTOR_SERVICE_TEST_H
#define JCPP_UTIL_CONCURRENT_LOCKS_JEXECUTOR_SERVICE_TEST_H

#include "jcpp/lang/JString.h"
#include "jcpp/util/concurrent/JAbstractTest.h"
#include "junit/framework/JTestCase.h"
#include "junit/framework/JTestSuite.h"

using namespace jcpp::io;
using namespace jcpp;

namespace jcpp{
    namespace util{
        namespace concurrent{

        	// @Class(canonicalName="jcpp.util.concurrent.locks.ExecutorServiceTest", simpleName="ExecutorServiceTest");
            class JCPP_EXPORT JExecutorServiceTest : public JAbstractTest{
            public:
                JExecutorServiceTest();

                static JClass* getClazz();

                virtual void test();

                virtual ~JExecutorServiceTest();
            };
        }
    }
}
#endif
