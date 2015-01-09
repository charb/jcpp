#ifndef JCPP_UTIL_JCONCURRENT_EXECUTION_REJECTED_EXCEPTION_TEST_H
#define JCPP_UTIL_JCONCURRENT_EXECUTION_REJECTED_EXCEPTION_TEST_H

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

        	// @Class(canonicalName="jcpp.util.concurrent.RejectedExecutionExceptionTest", simpleName="RejectedExecutionExceptionTest");
            class JCPP_EXPORT JRejectedExecutionExceptionTest : public JSerializableTest{
            public:
                JRejectedExecutionExceptionTest();

                static JClass* getClazz();

                virtual void equals(JObject* reached, JObject* expected);

                virtual JObject* getSerializableObject();

                virtual ~JRejectedExecutionExceptionTest();
            };
        }
    }
}
#endif
