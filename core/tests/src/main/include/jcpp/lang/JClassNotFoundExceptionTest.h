#ifndef JCPP_LANG_JCLASS_NOT_FOUND_EXCEPTION_TEST_H
#define JCPP_LANG_JCLASS_NOT_FOUND_EXCEPTION_TEST_H

#include "jcpp/lang/JString.h"
#include "jcpp/JSerializableTest.h"
#include "junit/framework/JTestCase.h"
#include "junit/framework/JTestSuite.h"
#include "jcpp/io/JObjectInputStream.h"
#include "jcpp/io/JObjectOutputStream.h"
#include "jcpp/lang/JClassNotFoundException.h"

using namespace jcpp::io;
using namespace jcpp;

namespace jcpp{
    namespace lang{

        //@Class(canonicalName="jcpp.lang.ClassNotFoundExceptionTest", simpleName="ClassNotFoundExceptionTest");
        class JCPP_EXPORT JClassNotFoundExceptionTest : public JSerializableTest{
        public:
            JClassNotFoundExceptionTest();

            static JClass* getClazz();

            virtual void equals(JObject* reached, JObject* expected);

            virtual JObject* getSerializableObject();

            virtual ~JClassNotFoundExceptionTest();
        };
    }
}
#endif
