#include "jcpp/io/JPrintStream.h"
#include "jcpp/JAbstractTest.h"
#include "jcpp/lang/JByte.h"
#include "jcpp/lang/JCharacter.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/nio/JHeapByteBuffer.h"
#include "jcpp/nio/JHeapByteBufferTest.h"

using namespace jcpp::nio;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp {
	namespace nio {

		JHeapByteBufferTest::JHeapByteBufferTest() :
				JTestCase(getClazz(), new JString("test")) {
		}

		JHeapByteBufferTest::~JHeapByteBufferTest() {
		}


		void JHeapByteBufferTest::test() {


			JHeapByteBuffer* tester = new JHeapByteBuffer(jint(1024), jint(1024));
			JByte *ByteToPut = new JByte();

			JPrimitiveByteArray *generatedBytes = new JPrimitiveByteArray(1024);

			for (int i = 0; i < 32; i++) {
				ByteToPut->set(jbyte(rand() % (0XFFFF)));
				tester->put(ByteToPut->get());
				generatedBytes->setByte(i, ByteToPut->get());
			}

			for (int i = 0; i < 32; i++) {

				assertEquals(generatedBytes->get(i), tester->get(i));
			}

			tester->clear();
			generatedBytes->finalize();
			generatedBytes = new JPrimitiveByteArray(1024);

			jint index;

			for (int i = 0; i < 1024; i++) {

				generatedBytes->setByte(i, jbyte(0));
			}

			for (int i = 0; i < 32; i++) {

				ByteToPut->set(jbyte(rand() % (0XFFFF)));
				index = rand() % 1024;
				tester->put(index, ByteToPut->get());
				generatedBytes->setByte(index, ByteToPut->get());

			}

			for (int i = 0; i < 32; i++) {
				assertEquals(generatedBytes->get(i), tester->get(i));
			}


			JCharacter *charToPut = new JCharacter();

			JPrimitiveCharArray *generatedChars = new JPrimitiveCharArray(1024);

			for (int i = 0; i < 32; i++) {
				charToPut->set(jchar(rand() % (0XFFFF)));
				tester->putChar(charToPut->get());
				generatedChars->setChar(i, charToPut->get());
			}

			for (int i = 0; i < 32; i++) {

				assertEquals(generatedChars->get(i), tester->getChar(2 * i));
			}

			tester->clear();
			generatedChars->finalize();
			generatedChars = new JPrimitiveCharArray(1024);


			for (int i = 0; i < 1024; i++) {

				generatedChars->setChar(i, jchar(0));
			}

			for (int i = 0; i < 32; i++) {

				charToPut->set(jchar(rand() % (0XFFFF)));
				index = rand() % 512;
				tester->putChar(2 * index, charToPut->get());
				generatedChars->setChar(index, charToPut->get());

			}

			for (int i = 0; i < 32; i++) {
				assertEquals(generatedChars->get(i), tester->getChar(2 * i));
			}

		}

	}
}
