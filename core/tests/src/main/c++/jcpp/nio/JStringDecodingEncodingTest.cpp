#include "jcpp/io/JFile.h"
#include "jcpp/io/JFileInputStream.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JPrimitiveByteArray.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/native/api/NativeInclude.h"
#include "jcpp/nio/JStringDecodingEncodingTest.h"
#include "jcpp/util/JList.h"
#include "jcpp/lang/JSystem.h"

using namespace jcpp::nio;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp {
	namespace nio {


		JStringDecodingEncodingTest::JStringDecodingEncodingTest() : JTestCase(getClazz(), new JString("testUtf8Encoding"))  {
		}

		JStringDecodingEncodingTest::~JStringDecodingEncodingTest() {
		}


		void JStringDecodingEncodingTest::testUtf8Encoding() {
			JString* expected = new JString("the quick brown fox jumps over the lazy dog THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG\t\n,.;:!?[](){}!1234567890!@#$%^&*~-");
			testEncoding(new JString("UTF-8"),expected);
		}


		void JStringDecodingEncodingTest::testEncoding(JString* encoding, JString* expected) {

			if(encoding==null)
			{
				throw new JIllegalArgumentException(new JString("Encoding String argument is null"));
			}

			if(expected==null)
			{
				throw new JIllegalArgumentException(new JString("Expected String argument is null"));
			}

			JString* path = new JString("../java-tests-results/jcpp/nio/StringEncodingTest");

			path = path->concat(new JString("_"));
			path = path->concat(encoding);
			path = path->concat(new JString(".strEncoding"));

			JFile *file = new JFile(path);
			JInputStream *is = new JFileInputStream(file);
			JPrimitiveByteArray* input = new JPrimitiveByteArray(256);
			jint readLength = is->read(input);
			JString* reached = new JString (input, 0 , readLength, encoding);

			assertEquals(expected,reached);

			JPrimitiveByteArray* resizedInput = new JPrimitiveByteArray(readLength);

			for(int i=0; i<readLength;i++)
			{
				resizedInput->setByte(i,input->getByte(i));
			}

			assertEquals(expected->getBytes(),resizedInput);


		}

	}
}
