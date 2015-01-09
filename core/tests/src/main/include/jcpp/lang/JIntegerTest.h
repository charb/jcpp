#ifndef JCPP_LANG_JINTEGER_TEST_H
#define JCPP_LANG_JINTEGER_TEST_H

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

        //@Class(canonicalName="jcpp.lang.IntegerTest", simpleName="IntegerTest");
        class JCPP_EXPORT JIntegerTest : public JSerializableTest{
        public:
            JIntegerTest();

            static JClass* getClazz();

            virtual JObject* getSerializableObject();

            virtual ~JIntegerTest();
        };
    }
}
#endif
