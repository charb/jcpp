#ifndef JCPP_LANG_REFLECT_JINVOCATION_TARGET_EXCEPTION_TEST_H
#define JCPP_LANG_REFLECT_JINVOCATION_TARGET_EXCEPTION_TEST_H

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
        namespace reflect{

           	//@Class(canonicalName="jcpp.lang.reflect.InvocationTargetExceptionTest", simpleName="InvocationTargetExceptionTest");
            class JCPP_EXPORT JInvocationTargetExceptionTest : public JSerializableTest{
            public:
                JInvocationTargetExceptionTest();

                static JClass* getClazz();

                virtual void equals(JObject* reached, JObject* expected);

                virtual JObject* getSerializableObject();

                virtual ~JInvocationTargetExceptionTest();
            };
        }
    }
}
#endif
