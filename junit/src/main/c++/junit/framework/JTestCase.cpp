#include "junit/framework/JTestCase.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JString.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "junit/framework/JAssert.h"
#include "jcpp/lang/JNoSuchMethodException.h"
#include "jcpp/lang/JStringBuilder.h"

namespace junit{
    namespace framework{

        JTestCase::JTestCase(JClass* _class):JAssert(_class){
            fName=null;            
        }

        JTestCase::JTestCase(JClass* _class,JString* name):JAssert(_class){
            fName=name;
        }

        JTestCase::JTestCase():JAssert(getClazz()){
            fName=null;
        }

        JTestCase::JTestCase(JString* name):JAssert(getClazz()){
            fName=name;
        }

        JTestResult* JTestCase::createResult(){
            return new JTestResult();
        }

        void JTestCase::setUp(){
        }

        void JTestCase::tearDown(){
        }

        jint JTestCase::countTestCases(){
            return 1;
        }

        JTestResult* JTestCase::run(){
            JTestResult* result = createResult();
            run(result);
            return result;
        }
        
        void JTestCase::run(JTestResult* result){
            result->run(this);
        }

        void JTestCase::runBare(){
            JThrowable* exception = null;
            setUp();
            try {
                runTest();
            } catch (JThrowable* running) {
                exception = running;
            }
            try {
                tearDown();
            } catch (JThrowable* tearingDown) {
                if (exception == null){
                    exception = tearingDown;
                }
            }
            if (exception != null){ 
                throw exception;
            }
        }

        void JTestCase::runTest(){
            assertNotNull(new JString("TestCase.fName cannot be null"), fName);
            JMethod* runMethod = null;
            try {
                runMethod = getClass()->getMethod(fName,null);
            } catch (JNoSuchMethodException* e) {
                JStringBuilder* builder=new JStringBuilder();
                builder->append(new JString("Method \""))->append(fName)->append("\" not found");
                fail(builder->toString());
            }
            if (!JModifier::isPublic(runMethod->getModifiers())) {
                JStringBuilder* builder=new JStringBuilder();
                builder->append(new JString("Method \""))->append(fName)->append("\" should be public");
                fail(builder->toString());
            }

            runMethod->invoke(this,null);
        }

        JString* JTestCase::toString(){
            JStringBuilder* builder=new JStringBuilder();
            builder->append(getName())->append("(")->append(getClass()->getName())->append(")");
            return builder->toString();
        }

        JString* JTestCase::getName(){
            return fName;
        }

        void JTestCase::setName(JString* name){
            this->fName=name;
        }

        void JTestCase::assertTrue(JString* message, jbool condition){
            JAssert::assertTrue(message,condition);
        }

        void JTestCase::assertTrue(jbool condition){
            JAssert::assertTrue(condition);
        }

        void JTestCase::assertFalse(JString* message, jbool condition){
            JAssert::assertFalse(message,condition);
        }

        void JTestCase::assertFalse(jbool condition){
            JAssert::assertFalse(condition);
        }
        
        void JTestCase::fail(JString* message){
            JAssert::fail(message);
        }

        void JTestCase::fail(){
            JAssert::fail();
        }

        void JTestCase::assertEquals(JString* message, JObject* expected, JObject* actual){
            JAssert::assertEquals(message,expected,actual);
        }

        void JTestCase::assertEquals(JObject* expected, JObject* actual){
            JAssert::assertEquals(expected,actual);
        }
        
        void JTestCase::assertEquals(JString* message, JString* expected, JString* actual){
            JAssert::assertEquals(message,expected,actual);
        }

        void JTestCase::assertEquals(JString* expected, JString* actual){
            JAssert::assertEquals(expected,actual);
        }

        void JTestCase::assertEquals(JString* message, jdouble expected, jdouble actual, jdouble delta){
            JAssert::assertEquals(message,expected,actual,delta);
        }

        void JTestCase::assertEquals(jdouble expected, jdouble actual, jdouble delta){
            JAssert::assertEquals(expected,actual,delta);
        }

        void JTestCase::assertEquals(JString* message, jfloat expected, jfloat actual, jfloat delta){
            JAssert::assertEquals(message,expected,actual,delta);
        }

        void JTestCase::assertEquals(jfloat expected, jfloat actual, jfloat delta){
            JAssert::assertEquals(expected,actual,delta);
        }

        void JTestCase::assertEquals(JString* message, jlong expected, jlong actual){
            JAssert::assertEquals(message,expected,actual);
        }

        void JTestCase::assertEquals(jlong expected, jlong actual){
            JAssert::assertEquals(expected,actual);
        }

        void JTestCase::assertEquals(JString* message, jbool expected, jbool actual){
            JAssert::assertEquals(message,expected,actual);
        }

        void JTestCase::assertEquals(jbool expected, jbool actual){
            JAssert::assertEquals(expected,actual);
        }

        void JTestCase::assertEquals(JString* message, jbyte expected, jbyte actual){
            JAssert::assertEquals(message,expected,actual);
        }

        void JTestCase::assertEquals(jbyte expected, jbyte actual){
            JAssert::assertEquals(expected,actual);
        }
        
        void JTestCase::assertEquals(JString* message, jchar expected, jchar actual){
            JAssert::assertEquals(message,expected,actual);
        }

        void JTestCase::assertEquals(jchar expected, jchar actual){
            JAssert::assertEquals(expected,actual);
        }

        void JTestCase::assertEquals(JString* message, jshort expected, jshort actual){
            JAssert::assertEquals(message,expected,actual);
        }

        void JTestCase::assertEquals(jshort expected, jshort actual){
            JAssert::assertEquals(expected,actual);
        }
        
        void JTestCase::assertEquals(JString* message, jint expected, jint actual){
            JAssert::assertEquals(message,expected,actual);
        }

        void JTestCase::assertEquals(jint expected, jint actual){
            JAssert::assertEquals(expected,actual);
        }
        
        void JTestCase::assertNotNull(JObject* object){
            JAssert::assertNotNull(object);
        }

        void JTestCase::assertNotNull(JString* message, JObject* object){
            JAssert::assertNotNull(message,object);
        }

        void JTestCase::assertNull(JObject* object){
            JAssert::assertNull(object);
        }

        void JTestCase::assertNull(JString* message, JObject* object){
            JAssert::assertNull(message,object);
        }

        void JTestCase::assertSame(JString* message, JObject* expected, JObject* actual){
            JAssert::assertSame(message,expected,actual);
        }

        void JTestCase::assertSame(JObject* expected, JObject* actual){
            JAssert::assertSame(expected,actual);
        }
        
        void JTestCase::assertNotSame(JString* message, JObject* expected, JObject* actual){
            JAssert::assertNotSame(message,expected,actual);
        }
        
        void JTestCase::assertNotSame(JObject* expected, JObject* actual){
            JAssert::assertNotSame(expected,actual);
        }
        
        void JTestCase::failSame(JString* message){
            JAssert::failSame(message);
        }

        void JTestCase::failNotSame(JString* message, JObject* expected, JObject* actual){
            JAssert::failNotSame(message,expected,actual);
        }

        void JTestCase::failNotEquals(JString* message, JObject* expected, JObject* actual){
            JAssert::failNotEquals(message,expected,actual);
        }

        JString* JTestCase::format(JString* message, JObject* expected, JObject* actual){
            return JAssert::format(message,expected,actual);
        }

        JTestCase::~JTestCase(){
        }
    }
}

