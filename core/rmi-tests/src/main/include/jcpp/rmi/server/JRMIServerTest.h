#ifndef JCPP_RMI_SERVER_TEST_CASE_H
#define JCPP_RMI_SERVER_TEST_CASE_H

#include "jcpp/lang/JString.h"
#include "jcpp/rmi/server/JAbstractTest.h"
#include "jcpp/rmi/server/transport/JEndPoint.h"
#include "junit/framework/JTestCase.h"
#include "junit/framework/JTestSuite.h"

using namespace jcpp::rmi::server::transport;
using namespace jcpp::io;
using namespace jcpp;

namespace jcpp{
    namespace rmi{
        namespace server{

        	// @Class(canonicalName="jcpp.rmi.server.RMIServerTest", simpleName="RMIServerTest");
            class JCPP_EXPORT JRMIServerTest : public JAbstractTest{
            public:
                JRMIServerTest();

                static JClass* getClazz();

                virtual void test(JEndPoint* localEndPoint1,jbool w);

                virtual void test();

                virtual ~JRMIServerTest();
            };
        }
    }
}
#endif
