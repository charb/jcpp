#ifndef JCPP_LANG_JCLASS_TEST_H
#define JCPP_LANG_JCLASS_TEST_H

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

        //@Class(canonicalName="jcpp.lang.ClassTest", simpleName="ClassTest");
        class JCPP_EXPORT JClassTest : public JSerializableTest{
        public:
            JClassTest();

            static JClass* getClazz();

            virtual JObject* getSerializableObject();

            virtual ~JClassTest();
        };
    }
}
#endif
