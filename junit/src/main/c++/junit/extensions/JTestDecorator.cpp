#include "junit/extensions/JTestDecorator.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JString.h"
#include "jcpp/lang/JObject.h"
#include "junit/framework/JTest.h"

namespace junit{
    namespace extensions{

        JTestDecorator::JTestDecorator(JClass* _class,JTest* test):JAssert(_class){
            fTest=test;
        }

        JTestDecorator::JTestDecorator(JTest* test):JAssert(getClazz()){
            fTest=test;
        }

        void JTestDecorator::basicRun(JTestResult* result){
            fTest->run(result);
        }
        
        jint JTestDecorator::countTestCases(){
            return fTest->countTestCases();
        }
        
        void JTestDecorator::run(JTestResult* result){
            basicRun(result);
        }
        
        JString* JTestDecorator::toString(){
            return (dynamic_cast<JObject*>(fTest))->toString();
        }
     
        JTest* JTestDecorator::getTest(){
            return fTest;
        }

        JTestDecorator::~JTestDecorator(){
        }
    }
}

