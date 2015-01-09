#ifndef JCPP_XML_PARSERS_TEST_CASE_H
#define JCPP_XML_PARSERS_TEST_CASE_H

#include "jcpp/lang/JString.h"
#include "jcpp/xml/parsers/JAbstractTest.h"
#include "junit/framework/JTestCase.h"
#include "junit/framework/JTestSuite.h"
#include "jcpp/util/JArrayList.h"
#include "jcpp/io/JFile.h"

using namespace jcpp::util;
using namespace jcpp::io;

namespace jcpp{
    namespace xml{
        namespace parsers{

        	// @Class(canonicalName="jcpp.xml.parsers.ParsersTest", simpleName="ParsersTest");
            class JCPP_EXPORT JParsersTest : public JAbstractTest{
            protected:
                void fill(JArrayList* list, JFile* file);

            public:
                JParsersTest();

                static JClass* getClazz();

                virtual void test();

                virtual ~JParsersTest();
            };
        }
    }
}
#endif
