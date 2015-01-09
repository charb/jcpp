#ifndef JCPP_LANG_JILLEGAL_MONITOR_STATE_EXCEPTION_TEST_H
#define JCPP_LANG_JILLEGAL_MONITOR_STATE_EXCEPTION_TEST_H

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

        //@Class(canonicalName="jcpp.lang.IllegalMonitorStateExceptionTest", simpleName="IllegalMonitorStateExceptionTest");
        class JCPP_EXPORT JIllegalMonitorStateExceptionTest : public JSerializableTest{
        public:
            JIllegalMonitorStateExceptionTest();

            static JClass* getClazz();

            virtual void equals(JObject* reached, JObject* expected);

            virtual JObject* getSerializableObject();

            virtual ~JIllegalMonitorStateExceptionTest();
        };
    }
}
#endif
