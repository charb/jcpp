#ifndef JCPP_LANG_JINCOMPATIBLE_CLASS_CHANGE_ERROR_TEST_H
#define JCPP_LANG_JINCOMPATIBLE_CLASS_CHANGE_ERROR_TEST_H

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

        //@Class(canonicalName="jcpp.lang.IncompatibleClassChangeErrorTest", simpleName="IncompatibleClassChangeErrorTest");
        class JCPP_EXPORT JIncompatibleClassChangeErrorTest : public JSerializableTest{
        public:
            JIncompatibleClassChangeErrorTest();

            static JClass* getClazz();

            virtual void equals(JObject* reached, JObject* expected);

            virtual JObject* getSerializableObject();

            virtual ~JIncompatibleClassChangeErrorTest();
        };
    }
}
#endif
