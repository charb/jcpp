#include "jcpp/io/JPrintStream.h"
#include "jcpp/lang/JSystem.h"
#include "jcpp/JAbstractTest.h"
#include "jcpp/lang/JCharacter.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/nio/JStringCharBuffer.h"
#include "jcpp/nio/JStringCharBufferTest.h"


using namespace jcpp::nio;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp {
	namespace nio {


		JStringCharBufferTest::JStringCharBufferTest() : JTestCase(getClazz(), new JString("test"))  {}

		JStringCharBufferTest::~JStringCharBufferTest() {}

		void JStringCharBufferTest::test(){

			JString* expected = new JString("the quick brown fox jumps over the lazy dog THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG\t\n,.;:!?[](){}!1234567890!@#$%^&*~-");

			JStringCharBuffer* tester = new JStringCharBuffer(expected,0,expected->length());

			for(int i = 0; i<expected->length();i++ )
			{
				assertEquals(expected->charAt(i),tester->get());
			}
			int rIdx;
			for (int i = 0; i<100; i++)
			{
				rIdx = rand()%expected->length();
				assertEquals(expected->charAt(rIdx),tester->get(rIdx));
			}
			assertEquals(expected,tester->toString(0,expected->length()));

		}

	}
}
