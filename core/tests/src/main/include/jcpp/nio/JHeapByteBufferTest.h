#ifndef JCPP_NIO_JHEAPBYTEBUFFER_TEST_H_
#define JCPP_NIO_JHEAPBYTEBUFFER_TEST_H_

#include "junit/framework/JTestCase.h"
#include "junit/framework/JTestSuite.h"
#include "jcpp/lang/JString.h"

using namespace junit::framework;
namespace jcpp {
	namespace nio {

	    //@Class(canonicalName="jcpp.nio.HeapByteBufferTest", simpleName="HeapByteBufferTest");
		 class JCPP_EXPORT JHeapByteBufferTest : public JTestCase {
		 public:
			 JHeapByteBufferTest();

			 static JClass* getClazz();

			 virtual void test();

			 virtual ~JHeapByteBufferTest();

		 };
	}
}



#endif
