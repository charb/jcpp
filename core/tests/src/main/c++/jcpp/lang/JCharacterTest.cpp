#include "jcpp/lang/JCharacterTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/JCharacter.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "jcpp/util/JArrays.h"
#include "jcpp/lang/JSystem.h"

using namespace jcpp::util;
using namespace jcpp::io;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JCharacterTest::JCharacterTest():JSerializableTest(getClazz()){

        	for (jint i = (jint)'a'; i <= (jint)'z'; ++i)
        		assertTrue(new JString("isJavaIdentifierPart error"), (new JCharacter())->isJavaIdentifierPart(i));
        	for (jint i = (jint)'A'; i <= (jint)'Z'; ++i)
        	    assertTrue(new JString("isJavaIdentifierPart error"), (new JCharacter())->isJavaIdentifierPart(i));
        	for (jint i = (jint)'0'; i <= (jint)'9'; ++i)
        	    assertTrue(new JString("isJavaIdentifierPart error"), (new JCharacter())->isJavaIdentifierPart(i));

        	assertTrue(new JString("isJavaIdentifierPart error"), (new JCharacter())->isJavaIdentifierPart((jint)'$'));
        	assertFalse(new JString("isJavaIdentifierPart error"), (new JCharacter())->isJavaIdentifierPart((jint)'.'));
        	assertFalse(new JString("isJavaIdentifierPart error"), (new JCharacter())->isJavaIdentifierPart((jint)' '));
        	assertFalse(new JString("isJavaIdentifierPart error"), (new JCharacter())->isJavaIdentifierPart((jint)'\n'));


        	for (jint i = (jint)'a'; i <= (jint)'z'; ++i)
        		assertEquals(new JString("upperCase error"), (new JCharacter())->toUpperCase(i), i - 32);
        	for (jint i = (jint)'A'; i <= (jint)'Z'; ++i)
        	    assertEquals(new JString("upperCase error"), (new JCharacter())->toUpperCase(i), i);
        	for (jint i = (jint)'0'; i <= (jint)'9'; ++i)
        	    assertEquals(new JString("upperCase error"), (new JCharacter())->toUpperCase(i), i);

        	assertEquals(new JString("upperCase error"), (new JCharacter())->toUpperCase((jint)'$'), (jint)'$');
        	assertEquals(new JString("upperCase error"), (new JCharacter())->toUpperCase((jint)' '), (jint)' ');
        	assertEquals(new JString("upperCase error"), (new JCharacter())->toUpperCase((jint)'\n'), (jint)'\n');

        	for (jint i = 65; i < 128; ++i)
        		if (i>=(jint)'A' && i<=(jint)'Z')
        			assertEquals(new JString("lowerCase error"), (new JCharacter())->toLowerCase(i), i + 32);
        		else
        			assertEquals(new JString("lowerCase error"), (new JCharacter())->toLowerCase(i), i);

        	for (jint i = (jint)'a'; i <= (jint)'z'; ++i)
        		assertFalse(new JString("isWhitespace error"), (new JCharacter())->isWhitespace(i));
        	for (jint i = (jint)'A'; i <= (jint)'Z'; ++i)
        	    assertFalse(new JString("isWhitespace error"), (new JCharacter())->isWhitespace(i));
        	for (jint i = (jint)'0'; i <= (jint)'9'; ++i)
        	    assertFalse(new JString("isWhitespace error"), (new JCharacter())->isWhitespace(i));

        	assertFalse(new JString("isWhitespace error"), (new JCharacter())->isWhitespace((jint)'$'));
        	assertTrue(new JString("isWhitespace error"), (new JCharacter())->isWhitespace((jint)' '));
        	assertTrue(new JString("isWhitespace error"), (new JCharacter())->isWhitespace((jint)'\t'));
        	assertTrue(new JString("isWhitespace error"), (new JCharacter())->isWhitespace((jint)'\n'));

        	for (jint i = 0; i <= 255; ++i){
        		if (i >= (jint)'0' && i <= (jint)'9')
        			assertTrue(new JString("isDigit error"), (new JCharacter())->isDigit(i));
        		else
        			assertFalse(new JString("isDigit error"), (new JCharacter())->isDigit(i));
        	}

        	jint expectation[] = {15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 12, 24, 24, 24, 26, 24, 24, 24, 21, 22, 24, 25, 24, 20, 24, 24, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 24, 24, 25, 25, 25, 24, 24, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 21, 24, 22, 27, 23, 27, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 21, 25, 22, 25, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 12, 24, 26, 26, 26, 26, 28, 28, 27, 28, 2, 29, 25, 16, 28, 27, 28, 25, 11, 11, 27, 2, 28, 24, 27, 11, 2, 30, 11, 11, 11, 24, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 25, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 25, 2, 2, 2, 2, 2, 2, 2, 2}; //taken from java
        	for (jint i = 0; i <= 255; ++i)
        		assertEquals(new JString("getType error"), (new JCharacter())->getType(i), expectation[i]);
        }

        void JCharacterTest::equals(JObject* reached, JObject* expected){
            JPrimitiveObjectArray* a1=dynamic_cast<JPrimitiveObjectArray*>(reached);
            JPrimitiveObjectArray* a2=dynamic_cast<JPrimitiveObjectArray*>(expected);
            assertTrue(new JString("Asserting that 2 char arrays are equals"),JArrays::equals(a1,a2));
        }

        JObject* JCharacterTest::getSerializableObject(){
            JPrimitiveObjectArray* a=new JPrimitiveObjectArray(JCharacter::getClazz(),3);
            a->set(0,new JCharacter((jchar)'c'));
            a->set(1,new JCharacter(JCharacter::MAX_VALUE));
            a->set(2,new JCharacter(JCharacter::MIN_VALUE));
            return a;
        }



        JCharacterTest::~JCharacterTest(){
        }
    }
}
