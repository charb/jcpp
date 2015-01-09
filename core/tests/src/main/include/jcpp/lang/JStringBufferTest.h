#ifndef JCPP_LANG_JSTRING_BUFFER_TEST_H
#define JCPP_LANG_JSTRING_BUFFER_TEST_H

#include "jcpp/lang/JStringBuffer.h"
#include "jcpp/JSerializableTest.h"
#include "junit/framework/JTestCase.h"
#include "junit/framework/JTestSuite.h"
#include "jcpp/io/JObjectInputStream.h"
#include "jcpp/io/JObjectOutputStream.h"

using namespace jcpp::io;
using namespace jcpp;

namespace jcpp{
    namespace lang{

        //@Class(canonicalName="jcpp.lang.StringBufferTest", simpleName="StringBufferTest");
        class JCPP_EXPORT JStringBufferTest : public JSerializableTest{
        public:
            JStringBufferTest();

            static JClass* getClazz();

            virtual JObject* getSerializableObject();

            virtual ~JStringBufferTest();
        };
    }
}
#endif
