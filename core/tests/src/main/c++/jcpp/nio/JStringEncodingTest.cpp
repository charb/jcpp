#include "jcpp/nio/JStringEncodingTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/JSystem.h"

using namespace jcpp::nio;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp {
	namespace nio {

	JStringEncodingTest::JStringEncodingTest(JString* name) : JAbstractTest(getClazz(), name)
	{	}

	JStringEncodingTest::~JStringEncodingTest()
	{	}


	void JStringEncodingTest::test()
	{
		JString* str = new JString("the quick brown fox jumps over the lazy dog THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG");
		JPrimitiveByteArray* ba = str->getBytes();

		JString* decodedStr = new JString(ba, 0, ba->size());

		assertEquals(str->length(), decodedStr->length());

		for (int i=0; i<str->length(); i++){
			assertEquals(str->charAt(i), decodedStr->charAt(i));
		}
	}


	}
}
