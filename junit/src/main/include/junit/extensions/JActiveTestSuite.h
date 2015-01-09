#ifndef JUNIT_FRAMEWORK_JACTIVE_TEST_SUITE_H
#define JUNIT_FRAMEWORK_JACTIVE_TEST_SUITE_H

#include "jcpp/lang/JObject.h"
#include "junit/framework/JTestSuite.h"

using namespace jcpp::lang;
using namespace junit::framework;

namespace junit{
    namespace extensions{
		// @Class(canonicalName="junit.extensions.ActiveTestSuite", simpleName="ActiveTestSuite");
        class JCPP_EXPORT JActiveTestSuite : public JTestSuite{
        	protected:
        		jint fActiveTestDeathCount;
        		virtual void waitUntilFinished();
        		virtual void runFinished();

            public:
                JActiveTestSuite();

                JActiveTestSuite(JClass* theClass);

                JActiveTestSuite(JString* name);

                JActiveTestSuite(JClass* theClass, JString* name);

                static JClass* getClazz();

				virtual void run(JTestResult* result);
				
				virtual void runTest(JTest* test, JTestResult* result);

                virtual ~JActiveTestSuite();
        };
    }
}
#endif
