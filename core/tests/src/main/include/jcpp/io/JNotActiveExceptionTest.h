#ifndef JCPP_IO_JNOT_ACTIVE_EXCEPTION_TEST_H
#define JCPP_IO_JNOT_ACTIVE_EXCEPTION_TEST_H

#include "jcpp/lang/JString.h"
#include "jcpp/JSerializableTest.h"
#include "junit/framework/JTestCase.h"
#include "junit/framework/JTestSuite.h"
#include "jcpp/io/JObjectInputStream.h"
#include "jcpp/io/JObjectOutputStream.h"

using namespace jcpp::lang;
using namespace jcpp;

namespace jcpp{
    namespace io{

       	//@Class(canonicalName="jcpp.io.NotActiveExceptionTest", simpleName="NotActiveExceptionTest");
        class JCPP_EXPORT JNotActiveExceptionTest : public JSerializableTest{
        public:
            JNotActiveExceptionTest();

            static JClass* getClazz();

            virtual void equals(JObject* reached, JObject* expected);

            virtual JObject* getSerializableObject();

            virtual ~JNotActiveExceptionTest();
        };
    }
}
#endif
