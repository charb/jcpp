#include "junit/textui/JTestRunner.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JString.h"
#include "jcpp/lang/JObject.h"
#include "junit/runner/JBaseTestRunner.h"
#include "junit/framework/JTestResult.h"
#include "jcpp/lang/JException.h"
#include "jcpp/lang/JSystem.h"
#include "jcpp/lang/JInteger.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"

using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace junit{
    namespace textui{

        JTestRunner::JTestRunner():JBaseTestRunner(getClazz()){
            fPrinter=new JResultPrinter(JSystem::out);
        }

        JTestRunner::JTestRunner(JPrintStream* writer):JBaseTestRunner(getClazz()){
            fPrinter=new JResultPrinter(writer);
        }

        JTestRunner::JTestRunner(JResultPrinter* printer):JBaseTestRunner(getClazz()){
            fPrinter=printer;
        }

        JTestResult* JTestRunner::createTestResult(){
            return new JTestResult();
        }
        
        void JTestRunner::pause(jbool w){
            if (!w){
                return;
            }
            fPrinter->printWaitPrompt();
            jint max=JInteger::MAX_VALUE;
            JSystem::in->read();
        }

        JTestResult* JTestRunner::runSingleMethod(JString* testCase, JString* method, jbool w){
            JClass* testClass = loadSuiteClass(testCase);
            JTest* test = JTestSuite::createTest(testClass, method);
            return doRun(test, w);
        }

        void JTestRunner::runFailed(JString* message){
            JSystem::out->println(message);
            JSystem::exit(FAILURE_EXIT);
        }

        jint JTestRunner::SUCCESS_EXIT = 0;

        jint JTestRunner::FAILURE_EXIT = 1;

        jint JTestRunner::EXCEPTION_EXIT = 2;        

        void JTestRunner::run(JClass* testClass){
            run(new JTestSuite(testClass));
        }

        JTestResult* JTestRunner::run(JTest* test){
            JTestRunner* runner = new JTestRunner();
            return runner->doRun(test);
        }

        void JTestRunner::runAndWait(JTest* suite){
            JTestRunner* aTestRunner = new JTestRunner();
            aTestRunner->doRun(suite, true);
        }

        void JTestRunner::testFailed(jint status, JTest* test, JThrowable* e){
        }

        void JTestRunner::testStarted(JString* testName){
        }

        void JTestRunner::testEnded(JString* testName){
        }

        JTestResult* JTestRunner::doRun(JTest* test){
            return doRun(test, false);
        }

        JTestResult* JTestRunner::doRun(JTest* suite, jbool w){
            JTestResult* result = createTestResult();
            result->addListener(fPrinter);
            jlong startTime = JSystem::currentTimeMillis();
            suite->run(result);
            jlong endTime = JSystem::currentTimeMillis();
            jlong runTime = endTime - startTime;
            fPrinter->print(result, runTime);
            pause(w);
            return result;
        }

        //TODO use cli project to parse and get suite class name to run
        void JTestRunner::main(JPrimitiveObjectArray* args){
            JTestRunner* aTestRunner = new JTestRunner();
            try {
                JTestResult* r = aTestRunner->start(args);
                if (!r->wasSuccessful()) {
                    //JSystem::exit(FAILURE_EXIT); TODO
                }
                //JSystem::exit(SUCCESS_EXIT); TODO
            } catch (JException* e) {
                JSystem::err->println(e->getMessage());
                // JSystem::exit(EXCEPTION_EXIT);
            }
        }

        JTestResult* JTestRunner::start(JPrimitiveObjectArray* args){
            JString* testCase = new JString("");
            JString* method = new JString("");
            jbool wait = false;
            for (jint i = 0; i < args->size(); i++) {
                JObject* o=args->get(i);
                if (o->equals(new JString("-wait"))) {
                    wait = true;

                } else if (o->equals(new JString("-c"))) {
                    testCase = extractClassName(dynamic_cast<JString*>(args->get(++i)));

                } else if (o->equals(new JString("-m"))) {
                    JString* arg = dynamic_cast<JString*>(args->get(++i));
                    jint lastIndex = arg->lastIndexOf('.');
                    testCase = arg->substring(0, lastIndex);
                    method = arg->substring(lastIndex + 1);

                } else {
                    testCase = dynamic_cast<JString*>(args->get(i));
                }
            }

            if (testCase->equals(new JString(""))) {
                throw new JException(new JString("Usage: TestRunner [-wait] testCaseName, where name is the name of the TestCase class"));
            }

            if (!method->equals(new JString(""))) {
                return runSingleMethod(testCase, method, wait);
            }
            JTest* suite = getTest(testCase);
            return doRun(suite, wait);
        }

        void JTestRunner::setPrinter(JResultPrinter* printer){
            fPrinter=printer;
        }

        JTestRunner::~JTestRunner(){
        }
    }
}

