#ifndef JCPP_LANG_JCLASS_FORMAT_ERROR_TEST_H
#define JCPP_LANG_JCLASS_FORMAT_ERROR_TEST_H

#include "jcpp/lang/JString.h"
#include "jcpp/JSerializableTest.h"
#include "junit/framework/JTestCase.h"
#include "junit/framework/JTestSuite.h"
#include "jcpp/io/JObjectInputStream.h"
#include "jcpp/io/JObjectOutputStream.h"
#include "jcpp/lang/JClassFormatError.h"

using namespace jcpp::io;
using namespace jcpp;

namespace jcpp{
    namespace lang{

        //@Class(canonicalName="jcpp.lang.ClassFormatErrorTest", simpleName="ClassFormatErrorTest");
        class JCPP_EXPORT JClassFormatErrorTest : public JSerializableTest{
        public:
            JClassFormatErrorTest();

            static JClass* getClazz();

            virtual void equals(JObject* reached, JObject* expected);

            virtual JObject* getSerializableObject();

            virtual ~JClassFormatErrorTest();
        };
    }
}
#endif
