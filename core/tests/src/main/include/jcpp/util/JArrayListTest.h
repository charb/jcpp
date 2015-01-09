#ifndef JCPP_UTIL_JARRAY_LIST_TEST_H
#define JCPP_UTIL_JARRAY_LIST_TEST_H

#include "jcpp/lang/JString.h"
#include "jcpp/JSerializableTest.h"
#include "junit/framework/JTestCase.h"
#include "junit/framework/JTestSuite.h"
#include "jcpp/io/JObjectInputStream.h"
#include "jcpp/io/JObjectOutputStream.h"

using namespace jcpp::io;
using namespace jcpp;

namespace jcpp{
    namespace util{

    	//@Class(canonicalName="jcpp.nio.ArrayListTest", simpleName="ArrayListTest");
        class JCPP_EXPORT JArrayListTest : public JSerializableTest{
        public:
            JArrayListTest();

            static JClass* getClazz();

            virtual void equals(JObject* reached, JObject* expected);

            virtual JObject* getSerializableObject();

            virtual ~JArrayListTest();
        };
    }
}
#endif
