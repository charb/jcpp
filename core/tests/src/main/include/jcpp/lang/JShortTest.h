#ifndef JCPP_LANG_JSHORT_TEST_H
#define JCPP_LANG_JSHORT_TEST_H

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

        //@Class(canonicalName="jcpp.lang.ShortTest", simpleName="ShortTest");
        class JCPP_EXPORT JShortTest : public JSerializableTest{
        public:
            JShortTest();

            static JClass* getClazz();

            virtual JObject* getSerializableObject();

            virtual ~JShortTest();
        };
    }
}
#endif
