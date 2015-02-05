#ifndef JCPP_NET_JSocketTimeoutExceptionTest_H_
#define JCPP_NET_JSocketTimeoutExceptionTest_H_

#include "jcpp/lang/JString.h"
#include "jcpp/JSerializableTest.h"
#include "junit/framework/JTestCase.h"
#include "junit/framework/JTestSuite.h"
#include "jcpp/io/JObjectInputStream.h"
#include "jcpp/io/JObjectOutputStream.h"

using namespace jcpp::io;
using namespace jcpp::lang;
using namespace jcpp;

namespace jcpp{
    namespace net{

       	//@Class(canonicalName="jcpp.net.SocketTimeoutExceptionTest", simpleName="SocketTimeoutExceptionTest");
        class JCPP_EXPORT JSocketTimeoutExceptionTest : public JSerializableTest{
        public:
        	JSocketTimeoutExceptionTest();

            static JClass* getClazz();

            virtual void equals(JObject* reached, JObject* expected);

            virtual JObject* getSerializableObject();

            virtual ~JSocketTimeoutExceptionTest();
        };
    }
}



#endif /* JCPP_NET_JSocketTimeoutExceptionTest_H_ */
