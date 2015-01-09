#include "junit/extensions/JActiveTestSuite.h"
#include "junit/framework/JTestSuite.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JString.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JThrowable.h"

namespace junit{
    namespace extensions{

        JActiveTestSuite::JActiveTestSuite():JTestSuite(getClazz(),false){
            fActiveTestDeathCount=0;
        }

        JActiveTestSuite::JActiveTestSuite(JClass* theClass):JTestSuite(getClazz(),theClass,false){
            fActiveTestDeathCount=0;
        }

        JActiveTestSuite::JActiveTestSuite(JString* name):JTestSuite(getClazz(),name,false){
            fActiveTestDeathCount=0;
        }

        JActiveTestSuite::JActiveTestSuite(JClass* theClass, JString* name):JTestSuite(getClazz(),theClass,name,false){
            fActiveTestDeathCount=0;
        }

        void JActiveTestSuite::run(JTestResult* result){
            fActiveTestDeathCount = 0;
            JTestSuite::run(result);
            waitUntilFinished();
        }
        
        void JActiveTestSuite::runTest(JTest* test, JTestResult* result){
            synchronized(this,{
                // TODO later, once JThread done
                // JThread* t = new JThread() {
                //     void run() {
                //         try {
                //             test.run(result);
                //         } finally {
                //             runFinished();
                //         }
                //     }
                // };
                // t->start();
                try{
                    test->run(result);
                }catch(JThrowable* th){
                    runFinished();
                    throw th;
                }
            })
        }

        void JActiveTestSuite::waitUntilFinished(){
            synchronized(this,{
                while (fActiveTestDeathCount < testCount()) {
                    wait();
                }
            })
        }

        void JActiveTestSuite::runFinished(){
            synchronized(this,{
                fActiveTestDeathCount++;
                notifyAll();
            })
        }

        JActiveTestSuite::~JActiveTestSuite(){
        }
    }
}

