#ifndef JCPP_UTIL_CONCURRENT_LOCKS_JLOCKS_TEST_H
#define JCPP_UTIL_CONCURRENT_LOCKS_JLOCKS_TEST_H

#include "jcpp/lang/JString.h"
#include "jcpp/util/concurrent/JAbstractTest.h"
#include "junit/framework/JTestCase.h"
#include "junit/framework/JTestSuite.h"

using namespace jcpp::io;
using namespace jcpp;

namespace jcpp{
    namespace util{
        namespace concurrent{
            namespace locks{

            	// @Class(canonicalName="jcpp.util.concurrent.locks.LocksTest", simpleName="LocksTest");
                class JCPP_EXPORT JLocksTest : public JAbstractTest{
                public:
                    JLocksTest();

                    static JClass* getClazz();

                    virtual void test();

                    virtual ~JLocksTest();
                };
            }
        }
    }
}
#endif
