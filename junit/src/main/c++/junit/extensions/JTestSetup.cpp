#include "junit/extensions/JTestSetup.h"
#include "junit/extensions/JTestDecorator.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JString.h"
#include "jcpp/lang/JObject.h"

namespace junit{
    namespace extensions{


        JTestSetup::JTestSetup(JTest* test):JTestDecorator(getClazz(),test){
        }

        void JTestSetup::setUp(){
        }

        void JTestSetup::tearDown(){
        }



    	// @Class(canonicalName="junit.extensions.AnonymousProtectable", simpleName="AnonymousProtectable");
        class JAnonymousProtectable : public JObject, public JProtectable{
            JTestSetup* test;
            JTestResult* result;

        public:
            static JClass* getClazz();

            JAnonymousProtectable(JTestSetup* test,JTestResult* result):JObject(getClazz()){
                this->test=test;
                this->result=result;
            }

            virtual void protect(){
                test->setUp();
                test->basicRun(result);
                test->tearDown();
            } 
        };

        void JTestSetup::run(JTestResult* result){
            JAnonymousProtectable* p=new JAnonymousProtectable(this,result);
            result->runProtected(this,p);
        }

        JTestSetup::~JTestSetup(){
        }
    }
}

