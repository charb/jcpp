#ifndef JUNIT_FRAMEWORK_JTEST_RESULT_H
#define JUNIT_FRAMEWORK_JTEST_RESULT_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JThrowable.h"
#include "jcpp/util/JList.h"
#include "jcpp/util/JIterator.h"
#include "junit/framework/JAssertionFailedError.h"
#include "junit/framework/JProtectable.h"

using namespace jcpp::lang;
using namespace jcpp::util;

namespace junit{
    namespace framework{
    	class JTest;
    	class JTestCase;
    	class JTestListener;

    	// @Class(canonicalName="junit.framework.TestResult", simpleName="TestResult");
        class JCPP_EXPORT JTestResult : public JObject{
        	protected:
				JList* fFailures;
    			JList* fErrors;
    			JList* fListeners;
    			jint fRunTests;
    			jbool fStop;

    			virtual void run(JTestCase* test);
    			friend class JTestCase;

            public:
                JTestResult();

                static JClass* getClazz();

                virtual void addError(JTest* test, JThrowable* e);
				
				virtual void addFailure(JTest* test, JAssertionFailedError* e);
				
				virtual void addListener(JTestListener* listener);

				virtual void removeListener(JTestListener* listener);

				virtual void endTest(JTest* test);

				virtual jint errorCount();
				
				virtual JIterator* errors();
				
				virtual jint failureCount();

				virtual JIterator* failures();

				virtual jint runCount();

				virtual void runProtected(JTest* test, JProtectable* p);
				
				virtual jbool shouldStop();
				
				virtual void startTest(JTest* test);

				virtual void stop();
				
				virtual jbool wasSuccessful();

                virtual ~JTestResult();
        };
    }
}
#endif
