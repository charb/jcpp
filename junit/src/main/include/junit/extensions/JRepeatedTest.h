#ifndef JUNIT_FRAMEWORK_JREPEATED_TEST_H
#define JUNIT_FRAMEWORK_JREPEATED_TEST_H

#include "jcpp/lang/JObject.h"
#include "junit/framework/JTest.h"
#include "junit/extensions/JTestDecorator.h"

using namespace jcpp::lang;
using namespace junit::framework;

namespace junit{
    namespace extensions{

		// @Class(canonicalName="junit.extensions.RepeatedTest", simpleName="RepeatedTest");
        class JCPP_EXPORT JRepeatedTest : public JTestDecorator{
        	protected:
        		jint fTimesRepeat;
            public:
				JRepeatedTest(JTest* test, jint repeat);

                static JClass* getClazz();
				
				virtual jint countTestCases();
				
				virtual void run(JTestResult* result);

				virtual JString* toString();
				
                virtual ~JRepeatedTest();
        };
    }
}
#endif
