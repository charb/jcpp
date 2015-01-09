#ifndef JCPP_IO_JIO_ERROR_TEST_H
#define JCPP_IO_JIO_ERROR_TEST_H

#include "jcpp/lang/JString.h"
#include "jcpp/JSerializableTest.h"
#include "junit/framework/JTestCase.h"
#include "junit/framework/JTestSuite.h"
#include "jcpp/io/JObjectInputStream.h"
#include "jcpp/io/JObjectOutputStream.h"

using namespace jcpp::lang;
using namespace jcpp;

namespace jcpp{
    namespace io{

       	//@Class(canonicalName="jcpp.io.IOErrorTest", simpleName="IOErrorTest");
        class JCPP_EXPORT JIOErrorTest : public JSerializableTest{
        public:
            JIOErrorTest();

            static JClass* getClazz();

            virtual void equals(JObject* reached, JObject* expected);

            virtual JObject* getSerializableObject();

            virtual ~JIOErrorTest();
        };
    }
}
#endif
