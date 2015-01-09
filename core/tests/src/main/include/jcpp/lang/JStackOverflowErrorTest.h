#ifndef JCPP_LANG_JSTACK_OVER_FLOW_ERROR_TEST_H
#define JCPP_LANG_JSTACK_OVER_FLOW_ERROR_TEST_H

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

        //@Class(canonicalName="jcpp.lang.StackOverflowErrorTest", simpleName="StackOverflowErrorTest");
    	class JCPP_EXPORT JStackOverflowErrorTest : public JSerializableTest{
        public:
            JStackOverflowErrorTest();

            static JClass* getClazz();

            virtual void equals(JObject* reached, JObject* expected);

            virtual JObject* getSerializableObject();

            virtual ~JStackOverflowErrorTest();
        };
    }
}
#endif
