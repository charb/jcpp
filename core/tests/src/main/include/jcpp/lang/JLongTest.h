#ifndef JCPP_LANG_JLONG_TEST_H
#define JCPP_LANG_JLONG_TEST_H

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

        //@Class(canonicalName="jcpp.lang.LongTest", simpleName="LongTest");
        class JCPP_EXPORT JLongTest : public JSerializableTest{
        public:
            JLongTest();

            static JClass* getClazz();

            virtual JObject* getSerializableObject();

            virtual ~JLongTest();
        };
    }
}
#endif
