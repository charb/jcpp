#ifndef JUNIT_FRAMEWORK_JTEST_LISTENER_H
#define JUNIT_FRAMEWORK_JTEST_LISTENER_H

#include "jcpp/lang/JInterface.h"
#include "junit/framework/JTest.h"
#include "jcpp/lang/JThrowable.h"
#include "junit/framework/JAssertionFailedError.h"

using namespace jcpp::lang;

namespace junit{
    namespace framework{
    	// @Class(canonicalName="junit.framework.TestListener", simpleName="TestListener");
        class JCPP_EXPORT JTestListener : public JInterface{
            public:
                static JClass* getClazz();

                virtual void addError(JTest* test, JThrowable* e)=0;

				virtual void addFailure(JTest* test, JAssertionFailedError* e)=0;

				virtual void endTest(JTest* test)=0;

				virtual void startTest(JTest* test)=0;

                virtual ~JTestListener();
        };
    }
}
#endif
