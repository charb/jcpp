#ifndef JCPP_IO_JIO_EXCEPTION_TEST_H
#define JCPP_IO_JIO_EXCEPTION_TEST_H

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

       	//@Class(canonicalName="jcpp.io.IOExceptionTest", simpleName="IOExceptionTest");
        class JCPP_EXPORT JIOExceptionTest : public JSerializableTest{
        public:
            JIOExceptionTest();

            static JClass* getClazz();

            virtual void equals(JObject* reached, JObject* expected);

            virtual JObject* getSerializableObject();

            virtual ~JIOExceptionTest();
        };
    }
}
#endif
