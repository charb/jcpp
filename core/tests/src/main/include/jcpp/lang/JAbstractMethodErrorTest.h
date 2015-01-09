#ifndef JCPP_LANG_JABSTRACT_METHOD_TEST_H
#define JCPP_LANG_JABSTRACT_METHOD_TEST_H

#include "jcpp/lang/JString.h"
#include "jcpp/JSerializableTest.h"
#include "junit/framework/JTestCase.h"
#include "junit/framework/JTestSuite.h"
#include "jcpp/io/JObjectInputStream.h"
#include "jcpp/io/JObjectOutputStream.h"
#include "jcpp/lang/JAbstractMethodError.h"

using namespace jcpp::io;
using namespace jcpp;

namespace jcpp{
    namespace lang{

       	//@Class(canonicalName="jcpp.lang.AbstractMethodErrorTest", simpleName="AbstractMethodErrorTest");
        class JCPP_EXPORT JAbstractMethodErrorTest : public JSerializableTest{
        public:
            JAbstractMethodErrorTest();

            static JClass* getClazz();

            virtual void equals(JObject* reached, JObject* expected);

            virtual JObject* getSerializableObject();

            virtual ~JAbstractMethodErrorTest();
        };
    }
}
#endif
