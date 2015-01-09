#ifndef JCPP_UTIL_CONCURRENT_ATOMIC_JATOMICS_TEST_H
#define JCPP_UTIL_CONCURRENT_ATOMIC_JATOMICS_TEST_H

#include "jcpp/lang/JString.h"
#include "jcpp/util/concurrent/JAbstractTest.h"
#include "junit/framework/JTestCase.h"
#include "junit/framework/JTestSuite.h"

using namespace jcpp::io;
using namespace jcpp;

namespace jcpp{
    namespace util{
        namespace concurrent{
            namespace atomic{
            	// @Class(canonicalName="jcpp.util.concurrent.atomic.AtomicsTest", simpleName="AtomicsTest");
                class JCPP_EXPORT JAtomicsTest : public JAbstractTest{
                public:
                    JAtomicsTest();

                    static JClass* getClazz();

                    virtual void test();

                    virtual ~JAtomicsTest();
                };
            }
        }
    }
}
#endif
