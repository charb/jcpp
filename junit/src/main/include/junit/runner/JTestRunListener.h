#ifndef JUNIT_RUNNER_JTEST_RUN_LISTENER_H
#define JUNIT_RUNNER_JTEST_RUN_LISTENER_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JString.h"

using namespace jcpp::lang;

namespace junit{
    namespace runner{
    	// @Class(canonicalName="junit.runner.TestRunListener", simpleName="TestRunListener");
        class JCPP_EXPORT JTestRunListener : public JInterface{
            public:
                static JClass* getClazz();

                static jint STATUS_ERROR;
    			
    			static jint STATUS_FAILURE;

    			virtual void testRunStarted(JString* testSuiteName, jint testCount)=0;

    			virtual void testRunEnded(jlong elapsedTime)=0;

    			virtual void testRunStopped(jlong elapsedTime)=0;

    			virtual void testStarted(JString* testName)=0;

    			virtual void testEnded(JString* testName)=0;

    			virtual void testFailed(jint status, JString* testName, JString* trace)=0;

                virtual ~JTestRunListener();
        };
    }
}
#endif
