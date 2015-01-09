#ifndef JCPP_LANG_JEXCEPTION_TEST_H
#define JCPP_LANG_JEXCEPTION_TEST_H

#include "jcpp/lang/JString.h"
#include "jcpp/JSerializableTest.h"
#include "junit/framework/JTestCase.h"
#include "junit/framework/JTestSuite.h"
#include "jcpp/io/JObjectInputStream.h"
#include "jcpp/io/JObjectOutputStream.h"

using namespace jcpp::io;
using namespace jcpp;

namespace jcpp{
    namespace lang{

        //@Class(canonicalName="jcpp.lang.ExceptionTest", simpleName="ExceptionTest");
        class JCPP_EXPORT JExceptionTest : public JSerializableTest{
        public:
            JExceptionTest();

            static JClass* getClazz();

            virtual void equals(JObject* reached, JObject* expected);

            virtual JObject* getSerializableObject();

            virtual ~JExceptionTest();
        };
    }
}
#endif
