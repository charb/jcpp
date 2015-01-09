#include "junit/framework/JAssert.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JString.h"
#include "jcpp/lang/JStringBuilder.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JDouble.h"
#include "jcpp/lang/JFloat.h"
#include "jcpp/lang/JShort.h"
#include "jcpp/lang/JInteger.h"
#include "jcpp/lang/JByte.h"
#include "jcpp/lang/JLong.h"
#include "jcpp/lang/JBoolean.h"
#include "jcpp/lang/JCharacter.h"
#include "junit/framework/JAssertionFailedError.h"
#include "junit/framework/JComparisonFailure.h"

namespace junit{
    namespace framework{

        JAssert::JAssert(JClass* _class):JObject(_class){
        }

        void JAssert::assertTrue(JString* message, jbool condition){
            if (!condition) {
                fail(message);
            }
        }

        void JAssert::assertTrue(jbool condition){
            assertTrue(null, condition);
        }

        void JAssert::assertFalse(JString* message, jbool condition){
            assertTrue(message, !condition);
        }

        void JAssert::assertFalse(jbool condition){
            assertFalse(null, condition);
        }
        
        void JAssert::fail(JString* message){
            if (message == null) {
                throw new JAssertionFailedError();
            }
            throw new JAssertionFailedError(message);
        }

        void JAssert::fail(){
            fail(null);
        }

        void JAssert::assertEquals(JString* message, JObject* expected, JObject* actual){
            if (expected == null && actual == null) {
                return;
            }
            if (expected != null && expected->equals(actual)) {
                return;
            }
            failNotEquals(message, expected, actual);
        }

        void JAssert::assertEquals(JObject* expected, JObject* actual){
            assertEquals(null, expected, actual);
        }
        
        void JAssert::assertEquals(JString* message, JString* expected, JString* actual){
            if (expected == null && actual == null) {
                return;
            }
            if (expected != null && expected->equals(actual)) {
                return;
            }
            JString* cleanMessage = (message == null ? new JString("") : message);
            throw new JComparisonFailure(cleanMessage, expected, actual);
        }

        void JAssert::assertEquals(JString* expected, JString* actual){
            assertEquals(null, expected, actual);
        }

        void JAssert::assertEquals(JString* message, jdouble expected, jdouble actual, jdouble delta){
            if (JDouble::compare(expected, actual) == 0) {
                return;
            }
            if (!(expected - actual <= delta)) {
                failNotEquals(message, new JDouble(expected), new JDouble(actual));
            }
        }

        void JAssert::assertEquals(jdouble expected, jdouble actual, jdouble delta){
            assertEquals(null, expected, actual, delta);
        }

        void JAssert::assertEquals(JString* message, jfloat expected, jfloat actual, jfloat delta){
            if (JFloat::compare(expected, actual) == 0) {
                return;
            }
            if (!((expected - actual) <= delta)) {
                failNotEquals(message, new JFloat(expected), new JFloat(actual));
            }
        }

        void JAssert::assertEquals(jfloat expected, jfloat actual, jfloat delta){
            assertEquals(null, expected, actual, delta);
        }

        void JAssert::assertEquals(JString* message, jlong expected, jlong actual){
            assertEquals(message, new JLong(expected), new JLong(actual));
        }

        void JAssert::assertEquals(jlong expected, jlong actual){
            assertEquals(null, expected, actual);
        }

        void JAssert::assertEquals(JString* message, jbool expected, jbool actual){
            assertEquals(message, new JBoolean(expected), new JBoolean(actual));
        }

        void JAssert::assertEquals(jbool expected, jbool actual){
            assertEquals(null, expected, actual);
        }

        void JAssert::assertEquals(JString* message, jbyte expected, jbyte actual){
            assertEquals(message, new JByte(expected), new JByte(actual));
        }

        void JAssert::assertEquals(jbyte expected, jbyte actual){
            assertEquals(null, expected, actual);
        }
        
        void JAssert::assertEquals(JString* message, jchar expected, jchar actual){
             assertEquals(message, new JCharacter(expected), new JCharacter(actual));
        }

        void JAssert::assertEquals(jchar expected, jchar actual){
            assertEquals(null, expected, actual);
        }

        void JAssert::assertEquals(JString* message, jshort expected, jshort actual){
            assertEquals(message, new JShort(expected), new JShort(actual));
        }

        void JAssert::assertEquals(jshort expected, jshort actual){
            assertEquals(null, expected, actual);
        }
        
        void JAssert::assertEquals(JString* message, jint expected, jint actual){
            assertEquals(message, new JInteger(expected), new JInteger(actual));
        }

        void JAssert::assertEquals(jint expected, jint actual){
            assertEquals(null, expected, actual);
        }
        
        void JAssert::assertNotNull(JObject* object){
            assertNotNull(null, object);
        }

        void JAssert::assertNotNull(JString* message, JObject* object){
            assertTrue(message, object != null);
        }

        void JAssert::assertNull(JObject* object){
            if (object != null) {
                JStringBuilder* builder=new JStringBuilder();
                builder->append(new JString("Expected: <null> but was: "))->append(object->toString());
                assertNull(builder->toString(),object);
            }
        }

        void JAssert::assertNull(JString* message, JObject* object){
            assertTrue(message, object == null);
        }

        void JAssert::assertSame(JString* message, JObject* expected, JObject* actual){
            if (expected == actual) {
                return;
            }
            failNotSame(message, expected, actual);
        }

        void JAssert::assertSame(JObject* expected, JObject* actual){
            assertSame(null, expected, actual);
        }
        
        void JAssert::assertNotSame(JString* message, JObject* expected, JObject* actual){
            if (expected == actual) {
                failSame(message);
            }
        }
        
        void JAssert::assertNotSame(JObject* expected, JObject* actual){
            assertNotSame(null, expected, actual);
        }
        
        void JAssert::failSame(JString* message){
            JStringBuilder* builder=new JStringBuilder();
            builder->append((message != null) ? message : new JString(""))->append(" ");
            builder->append(new JString("expected not same"));
            fail(builder->toString());
        }

        void JAssert::failNotSame(JString* message, JObject* expected, JObject* actual){
            JStringBuilder* builder=new JStringBuilder();
            builder->append((message != null) ? message : new JString(""))->append(" ");
            builder->append(new JString("expected same:<"))->append(expected->toString());
            builder->append(new JString("> was not:<"))->append(actual);
            builder->append(new JString(">"));
            fail(builder->toString());
        }

        void JAssert::failNotEquals(JString* message, JObject* expected, JObject* actual){
            fail(format(message, expected, actual));
        }

        JString* JAssert::format(JString* message, JObject* expected, JObject* actual){
            JStringBuilder* builder=new JStringBuilder();
            builder->append((message != null) ? message : new JString(""))->append(" ");
            builder->append("expected:<")->append(expected);
            builder->append("> but was:<")->append(actual)->append(new JString(">"));
            return builder->toString();
        }

        JAssert::~JAssert(){
        }
    }
}

