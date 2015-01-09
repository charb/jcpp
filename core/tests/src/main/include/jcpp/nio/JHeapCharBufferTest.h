#ifndef JCPP_NIO_JHEAPCharBUFFER_TEST_H_
#define JCPP_NIO_JHEAPCharBUFFER_TEST_H_

#include "junit/framework/JTestCase.h"
#include "junit/framework/JTestSuite.h"
#include "jcpp/lang/JString.h"

using namespace junit::framework;
namespace jcpp {
	namespace nio {

		//@Class(canonicalName="jcpp.nio.HeapCharBufferTest", simpleName="HeapCharBufferTest");
		 class JCPP_EXPORT JHeapCharBufferTest : public JTestCase {
		 public:
			 JHeapCharBufferTest();

			 static JClass* getClazz();

			 virtual void test();

			 virtual ~JHeapCharBufferTest();

		 };
	}
}



#endif
