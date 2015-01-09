#include "junit/runner/JBaseTestRunner.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JString.h"
#include "jcpp/lang/JStringBuilder.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClassNotFoundException.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "junit/runner/JTestRunListener.h"
#include "jcpp/io/JStringWriter.h"
#include "jcpp/io/JPrintWriter.h"

using namespace jcpp::io;

namespace junit{
    namespace runner{

        jint JBaseTestRunner::fgMaxMessageLength = 500;
        
        jbool JBaseTestRunner::fgFilterStack = true;

        JBaseTestRunner::JBaseTestRunner(JClass* _class):JObject(_class){
            fLoading=true;
        }

        JString* JBaseTestRunner::truncate(JString* s){
            if (fgMaxMessageLength != -1 && s->length() > fgMaxMessageLength) {
                JStringBuilder* builder=new JStringBuilder();
                s = s->substring(0, fgMaxMessageLength);
                builder->append(s)->append("...");
                s=builder->toString();
            }
            return s;
        }

        JString* JBaseTestRunner::getFilteredTrace(JThrowable* e){
            JStringWriter* stringWriter = new JStringWriter();
            JPrintWriter* writer = new JPrintWriter(stringWriter);
            e->printStackTrace(writer);
            JString* trace = stringWriter->toString();
            return trace;
        }

        jbool JBaseTestRunner::showStackRaw(){
            return true;
        }
        
        jbool JBaseTestRunner::filterLine(JString* line){
            return false;
        }

        JString* JBaseTestRunner::processArguments(JPrimitiveObjectArray* args){
            JString* suiteName = null;
            for (jint i = 0; i < args->size(); i++) {
                if (args[i].equals(new JString("-c"))) {
                    if (args->size() > i + 1) {
                        suiteName = extractClassName(dynamic_cast<JString*>(args->get(i + 1)));
                    }
                    i++;
                } else {
                    suiteName = dynamic_cast<JString*>(args->get(i));
                }
            }
            return suiteName;
        }

        JClass* JBaseTestRunner::loadSuiteClass(JString* suiteClassName){
            return getClass()->getClassLoader()->loadClass(suiteClassName);
        }

        void JBaseTestRunner::clearStatus(){
        }

        jbool JBaseTestRunner::useReloadingTestSuiteLoader(){
            return fLoading;
        }

        JString* JBaseTestRunner::SUITE_METHODNAME = new JString("suite");

        void JBaseTestRunner::startTest(JTest* test){
            synchronized(this,{
                testStarted((dynamic_cast<JObject*>(test))->toString());
            })
        }

        void JBaseTestRunner::endTest(JTest* test){
            synchronized(this,{
                testEnded((dynamic_cast<JObject*>(test))->toString());
            })
        }

        void JBaseTestRunner::addError(JTest* test, JThrowable* e){
            synchronized(this,{
                testFailed(JTestRunListener::STATUS_ERROR, test, e);
            })
        }

        void JBaseTestRunner::addFailure(JTest* test, JAssertionFailedError* e){
            synchronized(this,{
                testFailed(JTestRunListener::STATUS_FAILURE, test, e);
            })
        }

        JTest* JBaseTestRunner::getTest(JString* suiteClassName){
            if (suiteClassName->length() <= 0) {
                clearStatus();
                return null;
            }

            JClass* testClass = null;
            try {
                testClass = loadSuiteClass(suiteClassName);
            } catch (JClassNotFoundException* e) {
                JString* clazz = e->getMessage();
                if (clazz == null) {
                    clazz = suiteClassName;
                }
                JStringBuilder* builder=new JStringBuilder();
                builder->append("Class not found \"")->append(clazz->toString())->append("\"");
                runFailed(builder->toString());
                return null;

            } catch (JException* e) {
                JStringBuilder* builder=new JStringBuilder();
                builder->append("Error: ")->append(e->toString());
                runFailed(builder->toString());
                return null;
            }

            JMethod* suiteMethod = null;
            try {
                suiteMethod = testClass->getMethod(new JString(SUITE_METHODNAME),null);
            } catch (JException* e) {
                clearStatus();
                return new JTestSuite(testClass);
            }

            if (!JModifier::isStatic(suiteMethod->getModifiers())) {
                runFailed(new JString("Suite() method must be static"));
                return null;
            }

            JTest* test = null;
            try {
                test = dynamic_cast<JTest*>(suiteMethod->invoke(null,null));
                if (test == null) {
                    return test;
                }
            } catch (JThrowable* e) {
                JStringBuilder* builder=new JStringBuilder();
                builder->append("Failed to invoke suite(): ")->append(e->toString());
                runFailed(builder->toString());
                return null;
            }

            clearStatus();
            return test;
        }
        
        JString* JBaseTestRunner::elapsedTimeAsString(jlong runTime){
            jlong l=runTime/1000;
            return JString::valueOf(l);
        }

        void JBaseTestRunner::setLoading(jbool enable){
            fLoading=enable;
        }
        
        JString* JBaseTestRunner::extractClassName(JString* className){
            if (className->startsWith(new JString("Default package for"))) {
                return className->substring(className->lastIndexOf(new JString(".")) + 1);
            }
            return className;
        }

        JBaseTestRunner::~JBaseTestRunner(){
        }
    }
}

