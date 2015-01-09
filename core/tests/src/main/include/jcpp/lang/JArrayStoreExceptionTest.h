#ifndef JCPP_LANG_JARRAY_STORE_EXCEPTION_TEST_H
#define JCPP_LANG_JARRAY_STORE_EXCEPTION_TEST_H

#include "jcpp/lang/JString.h"
#include "jcpp/JSerializableTest.h"
#include "junit/framework/JTestCase.h"
#include "junit/framework/JTestSuite.h"
#include "jcpp/io/JObjectInputStream.h"
#include "jcpp/io/JObjectOutputStream.h"
#include "jcpp/lang/JArithmeticException.h"

using namespace jcpp::io;
using namespace jcpp;

namespace jcpp{
    namespace lang{

        //@Class(canonicalName="jcpp.lang.ArrayStoreExceptionTest", simpleName="ArrayStoreExceptionTest");
        class JCPP_EXPORT JArrayStoreExceptionTest : public JSerializableTest{
        public:
            JArrayStoreExceptionTest();

            static JClass* getClazz();

            virtual void equals(JObject* reached, JObject* expected);

            virtual JObject* getSerializableObject();

            virtual ~JArrayStoreExceptionTest();
        };
    }
}
#endif
