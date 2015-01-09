#ifndef JCPP_LANG_JNO_CLASS_DEF_FOUND_ERROR_TEST_H
#define JCPP_LANG_JNO_CLASS_DEF_FOUND_ERROR_TEST_H

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

        //@Class(canonicalName="jcpp.lang.NoClassDefFoundErrorTest", simpleName="NoClassDefFoundErrorTest");
        class JCPP_EXPORT JNoClassDefFoundErrorTest : public JSerializableTest{
        public:
            JNoClassDefFoundErrorTest();

            static JClass* getClazz();

            virtual void equals(JObject* reached, JObject* expected);

            virtual JObject* getSerializableObject();

            virtual ~JNoClassDefFoundErrorTest();
        };
    }
}
#endif
