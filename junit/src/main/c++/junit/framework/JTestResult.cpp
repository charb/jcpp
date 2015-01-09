#include "junit/framework/JTestResult.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JString.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/util/JArrayList.h"
#include "jcpp/util/JIterator.h"
#include "junit/framework/JTestCase.h"
#include "junit/framework/JTest.h"
#include "junit/framework/JTestListener.h"
#include "junit/framework/JTestFailure.h"

using namespace jcpp::util;

namespace junit{
    namespace framework{

        JTestResult::JTestResult():JObject(getClazz()){
            fFailures=new JArrayList();
            fErrors=new JArrayList();
            fListeners=new JArrayList();
            fRunTests=0;
            fStop=false;
        }

        void JTestResult::addError(JTest* test, JThrowable* e){
            synchronized(this,{
                fErrors->add(new JTestFailure(test, e));
                for (jint i=0;i<fListeners->size();i++){
                    JTestListener* l=dynamic_cast<JTestListener*>(fListeners->get(i));
                    l->addError(test,e);
                }
            })
        }
                
        void JTestResult::addFailure(JTest* test, JAssertionFailedError* e){
            synchronized(this,{
                fFailures->add(new JTestFailure(test, dynamic_cast<JThrowable*>(e)));
                for (jint i=0;i<fListeners->size();i++){
                    JTestListener* l=dynamic_cast<JTestListener*>(fListeners->get(i));
                    l->addFailure(test,e);
                }
            })
        }
                
        void JTestResult::addListener(JTestListener* listener){
            synchronized(this,{
                fListeners->add(dynamic_cast<JObject*>(listener));
            })
        }

        void JTestResult::removeListener(JTestListener* listener){
            synchronized(this,{
                fListeners->remove(dynamic_cast<JObject*>(listener));
            })
        }

        void JTestResult::endTest(JTest* test){
            for (jint i=0;i<fListeners->size();i++){
                JTestListener* l=dynamic_cast<JTestListener*>(fListeners->get(i));
                l->endTest(test);
            }
        }

        jint JTestResult::errorCount(){
            synchronized(this,{
                return fErrors->size();
            })
        }
                
        JIterator* JTestResult::errors(){
            synchronized(this,{
                return fErrors->iterator();
            })
        }
                
        jint JTestResult::failureCount(){
            synchronized(this,{
                return fFailures->size();
            })
        }

        JIterator* JTestResult::failures(){
            synchronized(this,{
                return fFailures->iterator();
            })
        }

        void JTestResult::run(JTestCase* test){
            startTest(test);
            try {
                test->runBare();
            } catch (JAssertionFailedError* e) {
                addFailure(test, e);
            } catch (JThrowable* e) {
                addError(test, e);
            }
            endTest(test);
        }

        jint JTestResult::runCount(){
            synchronized(this,{
                return fRunTests;
            })
        }

        void JTestResult::runProtected(JTest* test, JProtectable* p){
            try {
                p->protect();
            } catch (JAssertionFailedError* e) {
                addFailure(test, e);
            } catch (JThrowable* e) {
                addError(test, e);
            }
        }
                
        jbool JTestResult::shouldStop(){
            synchronized(this,{
                return fStop;
            })
        }
                
        void JTestResult::startTest(JTest* test){
            jint count = test->countTestCases();
            synchronized(this,{
                fRunTests += count;
            })
            for (jint i=0;i<fListeners->size();i++){
                JTestListener* l=dynamic_cast<JTestListener*>(fListeners->get(i));
                l->startTest(test);
            }
        }

        void JTestResult::stop(){
            synchronized(this,{
                fStop=true;
            })
        }
                
        jbool JTestResult::wasSuccessful(){
            synchronized(this,{
                return failureCount() == 0 && errorCount() == 0;
            })
        }

        JTestResult::~JTestResult(){
        }
    }
}

