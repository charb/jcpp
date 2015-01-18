#ifndef JCPP_LANG_JCHARACTER_TEST_H
#define JCPP_LANG_JCHARACTER_TEST_H

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

        //@Class(canonicalName="jcpp.lang.CharacterTest", simpleName="CharacterTest");
        class JCPP_EXPORT JCharacterTest : public JSerializableTest{
        public:
            JCharacterTest();

            static JClass* getClazz();

            virtual void equals(JObject* reached, JObject* expected);

            virtual JObject* getSerializableObject();

            virtual ~JCharacterTest();
        };
    }
}
#endif
