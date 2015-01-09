#include "junit/textui/JResultPrinter.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JString.h"
#include "jcpp/lang/JStringBuilder.h"
#include "jcpp/lang/JObject.h"

namespace junit{
    namespace textui{

        JResultPrinter::JResultPrinter(JPrintStream* writer) :JObject(getClazz()){
            this->fWriter=writer;
            fColumn=0;
        }

        void JResultPrinter::printWaitPrompt(){
            getWriter()->println();
            getWriter()->println(new JString("<RETURN> to continue"));
        }

        void JResultPrinter::printHeader(jlong runTime){
            getWriter()->println();
            JStringBuilder* builder=new JStringBuilder();
            builder->append("Time: ")->append(elapsedTimeAsString(runTime));
            getWriter()->println(builder->toString());
        }

        void JResultPrinter::printErrors(JTestResult* result){
            printDefects(result->errors(), result->errorCount(), new JString("error"));
        }

        void JResultPrinter::printFailures(JTestResult* result){
            printDefects(result->failures(), result->failureCount(), new JString("failure"));
        }

        void JResultPrinter::printDefects(JIterator* booBoos, jint count, JString* type){
            if (count == 0){
                return;
            }
            if (count == 1) {
                JStringBuilder* builder=new JStringBuilder();
                builder->append("There was ")->append(count)->append(" ")->append(type)->append(":");
                getWriter()->println(builder->toString());
            } else {
                JStringBuilder* builder=new JStringBuilder();
                builder->append("There were ")->append(count)->append(" ")->append(type)->append("s:");
                getWriter()->println(builder->toString());
            }
            for (jint i = 1; booBoos->hasNext(); i++) {
                printDefect(dynamic_cast<JTestFailure*>(booBoos->next()), i);
            }
        }

        void JResultPrinter::printDefectHeader(JTestFailure* booBoo, jint count){
            JStringBuilder* builder=new JStringBuilder();
            builder->append(count)->append(") ")->append(booBoo->failedTest());
            getWriter()->print(builder->toString());
        }

        void JResultPrinter::printDefectTrace(JTestFailure* booBoo){
            getWriter()->print(booBoo->trace());
        }

        void JResultPrinter::printFooter(JTestResult* result){
            if (result->wasSuccessful()) {
                getWriter()->println();
                getWriter()->print(new JString("OK"));
                JStringBuilder* builder=new JStringBuilder();
                builder->append(" (")->append(result->runCount())->append(" test")->append((result->runCount() == 1 ? new JString("") : new JString("s")));
                builder->append(")");
                getWriter()->println(builder->toString());

            } else {
                getWriter()->println();
                getWriter()->println(new JString("FAILURES!!!"));
                JStringBuilder* builder=new JStringBuilder();
                builder->append("Tests run: ")->append(result->runCount());
                builder->append(",  Failures: ")->append(result->failureCount());
                builder->append(",  Errors: ")->append(result->errorCount());
                getWriter()->println(builder->toString());
            }
            getWriter()->println();
        }

        JString* JResultPrinter::elapsedTimeAsString(jlong runTime){
            jlong l=runTime/1000;
            return JString::valueOf(l);
        }

        void JResultPrinter::print(JTestResult* result, jlong runTime){
            synchronized(this,{
                printHeader(runTime);
                printErrors(result);
                printFailures(result);
                printFooter(result);
            })
        }

        void JResultPrinter::printDefect(JTestFailure* booBoo, jint count){
            printDefectHeader(booBoo, count);
            printDefectTrace(booBoo);
        }

        JPrintStream* JResultPrinter::getWriter(){
            return fWriter;   
        }

        void JResultPrinter::addError(JTest* test, JThrowable* e){
            getWriter()->print(new JString("E"));
        }

        void JResultPrinter::addFailure(JTest* test, JAssertionFailedError* t){
            getWriter()->print(new JString("F"));
        }

        void JResultPrinter::endTest(JTest* test){
        }

        void JResultPrinter::startTest(JTest* test){
            getWriter()->print(new JString("."));
            if (fColumn++ >= 40) {
                getWriter()->println();
                fColumn = 0;
            }
        }

        JResultPrinter::~JResultPrinter(){
        }
    }
}

