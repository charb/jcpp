#ifndef JUNIT_FRAMEWORK_JTEST_DECORATOR_H
#define JUNIT_FRAMEWORK_JTEST_DECORATOR_H

#include "jcpp/lang/JObject.h"
#include "junit/framework/JTest.h"
#include "junit/framework/JAssert.h"

using namespace jcpp::lang;
using namespace junit::framework;

namespace junit{
    namespace extensions{
    	// @Class(canonicalName="junit.extensions.TestDecorator", simpleName="TestDecorator");
        class JCPP_EXPORT JTestDecorator : public JAssert, public JTest{
        	protected:
        		JTest* fTest;
        		JTestDecorator(JClass* _class,JTest* test);
            public:
				JTestDecorator(JTest* test);

                static JClass* getClazz();

				virtual void basicRun(JTestResult* result);
				
				virtual jint countTestCases();
				
				virtual void run(JTestResult* result);
				
				virtual JString* toString();
				
				virtual JTest* getTest();

                virtual ~JTestDecorator();
        };
    }
}
#endif
