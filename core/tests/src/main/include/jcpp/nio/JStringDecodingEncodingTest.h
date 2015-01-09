#ifndef JCPP_NIO_JSTRING_DECODING_ENCODING_TEST_H_
#define JCPP_NIO_JSTRING_DECODING_ENCODING_TEST_H_

#include "jcpp/lang/JString.h"
#include "junit/framework/JTestCase.h"
#include "junit/framework/JTestSuite.h"
#include "jcpp/JAbstractTest.h"


using namespace junit::framework;
namespace jcpp {
	namespace nio {

		//@Class(canonicalName="jcpp.nio.StringDecodingEncodingTest", simpleName="StringDecodingEncodingTest");
		 class JCPP_EXPORT JStringDecodingEncodingTest : public JTestCase {
		 public:
			 JStringDecodingEncodingTest();

			 static JClass* getClazz();

			 virtual void testUtf8Encoding();

			 virtual void testEncoding(JString* encoding, JString* expected);

			 virtual ~JStringDecodingEncodingTest();

		 };
	}
}



#endif
