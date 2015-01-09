#ifndef JCPP_NIO_JSTRINGENCODING_TEST_H
#define JCPP_NIO_JSTRINGENCODING_TEST_H

#include "jcpp/lang/JString.h"
#include "junit/framework/JTestCase.h"
#include "junit/framework/JTestSuite.h"
#include "jcpp/JAbstractTest.h"

using namespace junit::framework;

namespace jcpp {
	namespace nio {

	//@Class(canonicalName="jcpp.nio.StringEncodingTest", simpleName="StringEncodingTest");
	class JCPP_EXPORT JStringEncodingTest : public JAbstractTest {
	public:
		JStringEncodingTest(JString* name);

		static JClass* getClazz();

		virtual void test();

		virtual ~JStringEncodingTest();
	};

	}
}

#endif
