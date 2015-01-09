#ifndef JUNIT_RUNNER_JBASE_TEST_RUNNER_H
#define JUNIT_RUNNER_JBASE_TEST_RUNNER_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "junit/framework/JTest.h"
#include "junit/framework/JTestListener.h"
#include "junit/framework/JTestSuite.h"

using namespace jcpp::lang;
using namespace junit::framework;

namespace junit{
    namespace runner{
    	// @Class(canonicalName="junit.runner.BaseTestRunner", simpleName="BaseTestRunner");
        class JCPP_EXPORT JBaseTestRunner : public JObject, public JTestListener{
        	protected:
        		static jint fgMaxMessageLength;
    			static jbool fgFilterStack;
    			static JString* getFilteredTrace(JThrowable* e);
    			static jbool showStackRaw();
				static jbool filterLine(JString* line);
    			jbool fLoading;
    			
                JBaseTestRunner(JClass* _class);
    			
                virtual JString* processArguments(JPrimitiveObjectArray* args);
    			virtual JClass* loadSuiteClass(JString* suiteClassName);
    			virtual void clearStatus();
    			virtual jbool useReloadingTestSuiteLoader();

            public:
                static JClass* getClazz();

    			static JString* SUITE_METHODNAME;

    			virtual void startTest(JTest* test);

    			virtual void endTest(JTest* test);

				virtual void addError(JTest* test, JThrowable* e);

				virtual void addFailure(JTest* test, JAssertionFailedError* e);

				virtual void testStarted(JString* testName)=0;

    			virtual void testEnded(JString* testName)=0;

    			virtual void testFailed(jint status, JTest* test, JThrowable* e)=0;

				virtual JTest* getTest(JString* suiteClassName);
				
				virtual JString* elapsedTimeAsString(jlong runTime);

				virtual void setLoading(jbool enable);
				
				virtual JString* extractClassName(JString* className);

                static JString* truncate(JString* s);

    			virtual void runFailed(JString* message)=0;

                virtual ~JBaseTestRunner();
        };
    }
}
#endif
