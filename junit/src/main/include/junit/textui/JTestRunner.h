#ifndef JUNIT_TEXT_UI_JTEST_RUNNER_H
#define JUNIT_TEXT_UI_JTEST_RUNNER_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "junit/framework/JTest.h"
#include "junit/framework/JTestSuite.h"
#include "junit/runner/JBaseTestRunner.h"
#include "junit/textui/JResultPrinter.h"
#include "jcpp/io/JPrintStream.h"

using namespace jcpp::lang;
using namespace jcpp::io;
using namespace junit::framework;
using namespace junit::runner;

namespace junit{
    namespace textui{
    	// @Class(canonicalName="junit.textui.TestRunner", simpleName="TestRunner");
        class JCPP_EXPORT JTestRunner : public JBaseTestRunner{
        	protected:
        		JResultPrinter* fPrinter;
        		
                virtual JTestResult* createTestResult();
        		virtual void pause(jbool w);
        		virtual JTestResult* runSingleMethod(JString* testCase, JString* method, jbool w);
        		virtual void runFailed(JString* message);

            public:
                static jint SUCCESS_EXIT;
                static jint FAILURE_EXIT;
                static jint EXCEPTION_EXIT;

                JTestRunner();

                JTestRunner(JPrintStream* writer);

                JTestRunner(JResultPrinter* printer);

                static JClass* getClazz();

    			static void run(JClass* testClass);

    			static JTestResult* run(JTest* test);

				static void runAndWait(JTest* suite);

				virtual void testFailed(jint status, JTest* test, JThrowable* e);

				virtual void testStarted(JString* testName);

				virtual void testEnded(JString* testName);

				virtual JTestResult* doRun(JTest* test);

				virtual JTestResult* doRun(JTest* suite, jbool w);

    			static void main(JPrimitiveObjectArray* args);

				virtual JTestResult* start(JPrimitiveObjectArray* args);

				virtual void setPrinter(JResultPrinter* printer);

                virtual ~JTestRunner();
        };
    }
}
#endif
