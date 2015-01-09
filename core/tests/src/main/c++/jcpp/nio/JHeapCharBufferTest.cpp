#include "jcpp/io/JPrintStream.h"
#include "jcpp/JAbstractTest.h"
#include "jcpp/lang/JCharacter.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/nio/JHeapCharBuffer.h"
#include "jcpp/nio/JHeapCharBufferTest.h"


using namespace jcpp::nio;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp {
	namespace nio {

		JHeapCharBufferTest::JHeapCharBufferTest() : JTestCase(getClazz(), new JString("test"))  {
				}

		JHeapCharBufferTest::~JHeapCharBufferTest() {
				}

		void JHeapCharBufferTest::test(){

			JHeapCharBuffer* tester = new JHeapCharBuffer(jint(1024),jint(1024));

			JPrimitiveCharArray *generatedChars = new JPrimitiveCharArray(1024);

			JCharacter *charToPut = new JCharacter();

			for(int i = 0; i < 32;i++)
			{
				charToPut->set(jchar(rand()%(0XFFFF)));
				tester->put(charToPut->get());
				generatedChars->setChar(i,charToPut->get());
 			}

			for(int i = 0; i < 32; i++)
			{
				assertEquals(generatedChars->get(i),tester->get(i));
			}

			tester->clear();
			generatedChars->finalize();
			generatedChars = new JPrimitiveCharArray(1024);




			jint index;

			for(int i = 0; i < 1024;i++)
			{
				generatedChars->setChar(i,jchar(0));
			}

			for(int i = 0; i < 32;i++)
			{
				charToPut->set(jchar(rand()%(0XFFFF)));
				index = rand()%1024;
				tester->put(index,charToPut->get());
				generatedChars->setChar(index,charToPut->get());

 			}

			for(int i = 0; i < 32; i++)
			{
				assertEquals(generatedChars->get(i),tester->get(i));
			}

		}

	}
}
