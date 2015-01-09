#ifndef JUNIT_FRAMEWORK_JTEST_FAILURE_H
#define JUNIT_FRAMEWORK_JTEST_FAILURE_H

#include "jcpp/lang/JObject.h"
#include "junit/framework/JTest.h"
#include "jcpp/lang/JThrowable.h"

using namespace jcpp::lang;

namespace junit{
    namespace framework{
    	// @Class(canonicalName="junit.framework.TestFailure", simpleName="TestFailure");
        class JCPP_EXPORT JTestFailure : public JObject{
        	protected:
        		JTest* fFailedTest;
    			JThrowable* fThrownException;

            public:
                static JClass* getClazz();

                JTestFailure(JTest* failedTest, JThrowable* thrownException);

                virtual JTest* failedTest();

                virtual JThrowable* thrownException();

                virtual JString* trace();

                virtual JString* exceptionMessage();

                virtual jbool isFailure();

                virtual JString* toString();

                virtual ~JTestFailure();
        };
    }
}
#endif
