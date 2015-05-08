#ifndef JCPP_OUTLOOK_TEST_CASE_H
#define JCPP_OUTLOOK_TEST_CASE_H

#include "jcpp/lang/JString.h"
#include "jcpp/rmi/server/transport/JEndPoint.h"
#include "junit/framework/JTestSuite.h"
#include "junit/framework/JTestCase.h"

using namespace jcpp::rmi::server::transport;
using namespace jcpp::io;
using namespace junit::framework;

namespace jcpp{
    namespace outlook{
        namespace tests{

        	// @Class(canonicalName="outlook.tests.OutlookTest", simpleName="OutlookTest");
            class JCPP_EXPORT JOutlookTest : public JTestCase{
            public:
                JOutlookTest();

                static JClass* getClazz();

                virtual void test();

                virtual ~JOutlookTest();
            };
        }
    }
}
#endif
