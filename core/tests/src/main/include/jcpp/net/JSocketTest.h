#ifndef JCPP_NET_JSOCKET_TEST_H_
#define JCPP_NET_JSOCKET_TEST_H_

#include "jcpp/lang/JString.h"
#include "jcpp/JSerializableTest.h"
#include "junit/framework/JTestCase.h"
#include "junit/framework/JTestSuite.h"
#include "jcpp/io/JObjectInputStream.h"
#include "jcpp/io/JObjectOutputStream.h"

using namespace jcpp::net;
using namespace jcpp;
using namespace junit::framework;

namespace jcpp{
	namespace net{
		//@Class(canonicalName="jcpp.net.SocketTest",simpleName="SocketTest");
		class JCPP_EXPORT JSocketTest:public JTestCase{
		public:

			JString* testerString;
			JSocketTest();

            static JClass* getClazz();

			 virtual void test();

			 virtual ~JSocketTest();


		};

	}
}

#endif /* JCPP_NET_JSOCKET_TEST_H_ */
