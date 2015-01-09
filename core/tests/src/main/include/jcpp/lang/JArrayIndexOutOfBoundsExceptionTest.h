#ifndef JCPP_LANG_JARRAY_INDEX_OUTOF_BOUNDS_EXCEPTION_TEST_H
#define JCPP_LANG_JARRAY_INDEX_OUTOF_BOUNDS_EXCEPTION_TEST_H

#include "jcpp/lang/JString.h"
#include "jcpp/JSerializableTest.h"
#include "junit/framework/JTestCase.h"
#include "junit/framework/JTestSuite.h"
#include "jcpp/io/JObjectInputStream.h"
#include "jcpp/io/JObjectOutputStream.h"
#include "jcpp/lang/JArrayIndexOutOfBoundsException.h"

using namespace jcpp::io;
using namespace jcpp;

namespace jcpp{
    namespace lang{

        //@Class(canonicalName="jcpp.lang.ArrayIndexOutOfBoundsExceptionTest", simpleName="ArrayIndexOutOfBoundsExceptionTest");
        class JCPP_EXPORT JArrayIndexOutOfBoundsExceptionTest : public JSerializableTest{
        public:
            JArrayIndexOutOfBoundsExceptionTest();

            static JClass* getClazz();

            virtual void equals(JObject* reached, JObject* expected);

            virtual JObject* getSerializableObject();

            virtual ~JArrayIndexOutOfBoundsExceptionTest();
        };
    }
}
#endif
