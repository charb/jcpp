#ifndef JCPP_LANG_JCLASS_CAST_EXCEPTION_TEST_H
#define JCPP_LANG_JCLASS_CAST_EXCEPTION_TEST_H

#include "jcpp/lang/JString.h"
#include "jcpp/JSerializableTest.h"
#include "junit/framework/JTestCase.h"
#include "junit/framework/JTestSuite.h"
#include "jcpp/io/JObjectInputStream.h"
#include "jcpp/io/JObjectOutputStream.h"
#include "jcpp/lang/JClassCastException.h"

using namespace jcpp::io;
using namespace jcpp;

namespace jcpp{
    namespace lang{

        //@Class(canonicalName="jcpp.lang.ClassCastExceptionTest", simpleName="ClassCastExceptionTest");
        class JCPP_EXPORT JClassCastExceptionTest : public JSerializableTest{
        public:
            JClassCastExceptionTest();

            static JClass* getClazz();

            virtual void equals(JObject* reached, JObject* expected);

            virtual JObject* getSerializableObject();

            virtual ~JClassCastExceptionTest();
        };
    }
}
#endif
