#ifndef JCPP_UTIL_JCONCURRENT_CANCELLATION_EXCEPTION_TEST_H
#define JCPP_UTIL_JCONCURRENT_CANCELLATION_EXCEPTION_TEST_H

#include "jcpp/lang/JString.h"
#include "jcpp/util/concurrent/JSerializableTest.h"
#include "junit/framework/JTestCase.h"
#include "junit/framework/JTestSuite.h"
#include "jcpp/io/JObjectInputStream.h"
#include "jcpp/io/JObjectOutputStream.h"

using namespace jcpp::io;
using namespace jcpp;

namespace jcpp{
    namespace util{
        namespace concurrent{

        	//@Class(canonicalName="jcpp.util.concurrent.CancellationExceptionTest", simpleName="CancellationExceptionTest");
            class JCPP_EXPORT JCancellationExceptionTest : public JSerializableTest{
            public:
                JCancellationExceptionTest();

                static JClass* getClazz();

                virtual void equals(JObject* reached, JObject* expected);

                virtual JObject* getSerializableObject();

                virtual ~JCancellationExceptionTest();
            };
        }
    }
}
#endif
