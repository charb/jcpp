#ifndef JCPP_LANG_JUNSUPPORTED_CLASS_VERSION_ERROR_TEST_H
#define JCPP_LANG_JUNSUPPORTED_CLASS_VERSION_ERROR_TEST_H

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

        //@Class(canonicalName="jcpp.lang.UnsupportedClassVersionErrorTest", simpleName="UnsupportedClassVersionErrorTest");
        class JCPP_EXPORT JUnsupportedClassVersionErrorTest : public JSerializableTest{
        public:
            JUnsupportedClassVersionErrorTest();

            static JClass* getClazz();

            virtual void equals(JObject* reached, JObject* expected);

            virtual JObject* getSerializableObject();

            virtual ~JUnsupportedClassVersionErrorTest();
        };
    }
}
#endif
