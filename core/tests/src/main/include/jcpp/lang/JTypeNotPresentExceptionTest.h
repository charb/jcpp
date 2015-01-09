#ifndef JCPP_LANG_JTYPE_NOT_PRESENT_EXCEPTION_TEST_H
#define JCPP_LANG_JTYPE_NOT_PRESENT_EXCEPTION_TEST_H

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

        //@Class(canonicalName="jcpp.lang.TypeNotPresentExceptionTest", simpleName="TypeNotPresentExceptionTest");
        class JCPP_EXPORT JTypeNotPresentExceptionTest : public JSerializableTest{
        public:
            JTypeNotPresentExceptionTest();

            static JClass* getClazz();

            virtual void equals(JObject* reached, JObject* expected);

            virtual JObject* getSerializableObject();

            virtual ~JTypeNotPresentExceptionTest();
        };
    }
}
#endif
