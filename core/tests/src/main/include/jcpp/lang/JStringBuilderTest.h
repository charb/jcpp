#ifndef JCPP_LANG_JSTRING_BUILDER_TEST_H
#define JCPP_LANG_JSTRING_BUILDER_TEST_H

#include "jcpp/lang/JStringBuilder.h"
#include "jcpp/JSerializableTest.h"
#include "junit/framework/JTestCase.h"
#include "junit/framework/JTestSuite.h"
#include "jcpp/io/JObjectInputStream.h"
#include "jcpp/io/JObjectOutputStream.h"

using namespace jcpp::io;
using namespace jcpp;

namespace jcpp{
    namespace lang{

        //@Class(canonicalName="jcpp.lang.StringBuilderTest", simpleName="StringBuilderTest");
        class JCPP_EXPORT JStringBuilderTest : public JSerializableTest{
        public:
            JStringBuilderTest();

            static JClass* getClazz();

            virtual JObject* getSerializableObject();

            virtual ~JStringBuilderTest();
        };
    }
}
#endif
