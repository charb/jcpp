#ifndef JCPP_LANG_JSTRING_TEST_H
#define JCPP_LANG_JSTRING_TEST_H

#include "jcpp/lang/JString.h"
#include "jcpp/JAbstractTest.h"
#include "junit/framework/JTestCase.h"
#include "junit/framework/JTestSuite.h"

using namespace junit::framework;

namespace jcpp{
    namespace lang{

        //@Class(canonicalName="jcpp.lang.StringTest", simpleName="StringTest");
        class JCPP_EXPORT JStringTest : public JAbstractTest{
        public:
            JStringTest(JString* name);

            static JClass* getClazz();

            virtual void testNewString();

            virtual ~JStringTest();
        };
    }
}
#endif
