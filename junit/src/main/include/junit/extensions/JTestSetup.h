#ifndef JUNIT_FRAMEWORK_JTEST_SETUP_H
#define JUNIT_FRAMEWORK_JTEST_SETUP_H

#include "jcpp/lang/JObject.h"
#include "junit/framework/JTest.h"
#include "junit/extensions/JTestDecorator.h"

using namespace jcpp::lang;
using namespace junit::framework;

namespace junit{
    namespace extensions{
		// @Class(canonicalName="junit.extensions.TestSetup", simpleName="TestSetup");
        class JCPP_EXPORT JTestSetup : public JTestDecorator{
        	protected:
        		virtual void setUp();
        		virtual void tearDown();
        		friend class JAnonymousProtectable;

            public:
				JTestSetup(JTest* test);

                static JClass* getClazz();

				virtual void run(JTestResult* result);

                virtual ~JTestSetup();
        };
    }
}
#endif
