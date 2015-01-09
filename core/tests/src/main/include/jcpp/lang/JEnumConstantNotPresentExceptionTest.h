#ifndef JCPP_LANG_JENUM_CONSTANT_NOT_SUPPORTED_EXCEPTION_TEST_H
#define JCPP_LANG_JENUM_CONSTANT_NOT_SUPPORTED_EXCEPTION_TEST_H

#include "jcpp/lang/JString.h"
#include "jcpp/JSerializableTest.h"
#include "junit/framework/JTestCase.h"
#include "junit/framework/JTestSuite.h"
#include "jcpp/io/JObjectInputStream.h"
#include "jcpp/io/JObjectOutputStream.h"
#include "jcpp/lang/JCloneNotSupportedException.h"

using namespace jcpp::io;
using namespace jcpp;

namespace jcpp{
    namespace lang{

        //@Class(canonicalName="jcpp.lang.EnumConstantNotPresentExceptionTest", simpleName="EnumConstantNotPresentExceptionTest");
        class JCPP_EXPORT JEnumConstantNotPresentExceptionTest : public JSerializableTest{
        public:
            JEnumConstantNotPresentExceptionTest();

            static JClass* getClazz();

            virtual void equals(JObject* reached, JObject* expected);

            virtual JObject* getSerializableObject();

            virtual ~JEnumConstantNotPresentExceptionTest();
        };
    }
}
#endif
