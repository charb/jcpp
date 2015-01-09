#ifndef JCPP_LANG_JBOOTSTRAP_METHOD_ERROR_TEST_H
#define JCPP_LANG_JBOOTSTRAP_METHOD_ERROR_TEST_H

#include "jcpp/lang/JString.h"
#include "jcpp/JSerializableTest.h"
#include "junit/framework/JTestCase.h"
#include "junit/framework/JTestSuite.h"
#include "jcpp/io/JObjectInputStream.h"
#include "jcpp/io/JObjectOutputStream.h"
#include "jcpp/lang/JBootstrapMethodError.h"

using namespace jcpp::io;
using namespace jcpp;

namespace jcpp{
    namespace lang{

        //@Class(canonicalName="jcpp.lang.BootstrapMethodErrorTest", simpleName="BootstrapMethodErrorTest");
        class JCPP_EXPORT JBootstrapMethodErrorTest : public JSerializableTest{
        public:
            JBootstrapMethodErrorTest();

            static JClass* getClazz();

            virtual void equals(JObject* reached, JObject* expected);

            virtual JObject* getSerializableObject();

            virtual ~JBootstrapMethodErrorTest();
        };
    }
}
#endif
