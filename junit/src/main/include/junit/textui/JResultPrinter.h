#ifndef JUNIT_TEXT_UI_JRESULT_PRINTER_H
#define JUNIT_TEXT_UI_JRESULT_PRINTER_H

#include "jcpp/lang/JObject.h"
#include "junit/framework/JTest.h"
#include "junit/framework/JTestListener.h"
#include "junit/framework/JTestSuite.h"
#include "junit/framework/JTestResult.h"
#include "junit/framework/JTestFailure.h"
#include "jcpp/util/JIterator.h"
#include "jcpp/io/JPrintStream.h"

using namespace jcpp::lang;
using namespace jcpp::io;
using namespace jcpp::util;
using namespace junit::framework;

namespace junit{
    namespace textui{
    	// @Class(canonicalName="junit.textui.ResultPrinter", simpleName="ResultPrinter");
        class JCPP_EXPORT JResultPrinter : public JObject, public JTestListener{
        	protected:
        		JPrintStream* fWriter;
    			jint fColumn;
                void print(JTestResult* result, jlong runTime);
    			void printWaitPrompt();
    			void printHeader(jlong runTime);
    			void printErrors(JTestResult* result);
    			void printFailures(JTestResult* result);
    			void printDefects(JIterator* booBoos, jint count, JString* type);
    			void printDefectHeader(JTestFailure* booBoo, jint count);
    			void printDefectTrace(JTestFailure* booBoo);
    			void printFooter(JTestResult* result);
    			JString* elapsedTimeAsString(jlong runTime);
    			friend class JTestRunner;

            public:
    			JResultPrinter(JPrintStream* writer);

                static JClass* getClazz();
				
    			virtual void printDefect(JTestFailure* booBoo, jint count);

				virtual JPrintStream* getWriter();

				virtual void addError(JTest* test, JThrowable* e);

				virtual void addFailure(JTest* test, JAssertionFailedError* t);

				virtual void endTest(JTest* test);

				virtual void startTest(JTest* test);

                virtual ~JResultPrinter();
        };
    }
}
#endif
