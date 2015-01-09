#ifndef JCPP_RMI_SERVER_TEST_SUITE_H
#define JCPP_RMI_SERVER_TEST_SUITE_H

#include "jcpp/lang/JString.h"
#include "junit/framework/JTestSuite.h"

using namespace junit::framework;

namespace jcpp{
	namespace rmi{
		namespace server{

			// @Class(canonicalName="jcpp.rmi.server.RMIServerTestSuite", simpleName="RMIServerTestSuite");
		    class JCPP_EXPORT JRMIServerTestSuite : public JTestSuite{
		    public:
		        JRMIServerTestSuite();

		        static JClass* getClazz();

		        static JRMIServerTestSuite* suite();

		        virtual ~JRMIServerTestSuite();
		    };
		}
	}
}
#endif
